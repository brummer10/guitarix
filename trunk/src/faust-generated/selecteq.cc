// generated from file '../src/faust/selecteq.dsp' by dsp2cc:
// Code generated with Faust 0.9.73 (http://faust.grame.fr)


namespace selecteq {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	FAUSTFLOAT 	fslider0;
	double 	fRec0[2];
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT 	fslider2;
	double 	fConst0;
	FAUSTFLOAT 	fslider3;
	double 	fRec2[2];
	FAUSTFLOAT 	fslider4;
	FAUSTFLOAT 	fslider5;
	FAUSTFLOAT 	fslider6;
	double 	fRec4[2];
	FAUSTFLOAT 	fslider7;
	FAUSTFLOAT 	fslider8;
	FAUSTFLOAT 	fslider9;
	double 	fRec6[2];
	FAUSTFLOAT 	fslider10;
	FAUSTFLOAT 	fslider11;
	FAUSTFLOAT 	fslider12;
	double 	fRec8[2];
	FAUSTFLOAT 	fslider13;
	FAUSTFLOAT 	fslider14;
	FAUSTFLOAT 	fslider15;
	double 	fRec10[2];
	FAUSTFLOAT 	fslider16;
	FAUSTFLOAT 	fslider17;
	FAUSTFLOAT 	fslider18;
	double 	fRec12[2];
	FAUSTFLOAT 	fslider19;
	FAUSTFLOAT 	fslider20;
	FAUSTFLOAT 	fslider21;
	double 	fRec14[2];
	FAUSTFLOAT 	fslider22;
	FAUSTFLOAT 	fslider23;
	FAUSTFLOAT 	fslider24;
	double 	fRec16[2];
	FAUSTFLOAT 	fslider25;
	FAUSTFLOAT 	fslider26;
	FAUSTFLOAT 	fslider27;
	double 	fRec18[2];
	FAUSTFLOAT 	fslider28;
	FAUSTFLOAT 	fslider29;
	double 	fRec19[3];
	double 	fRec17[3];
	double 	fRec15[3];
	double 	fRec13[3];
	double 	fRec11[3];
	double 	fRec9[3];
	double 	fRec7[3];
	double 	fRec5[3];
	double 	fRec3[3];
	double 	fRec1[3];
	void clear_state_f();
	int load_ui_f(const UiBuilder& b, int form);
	static const char *glade_def;
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



Dsp::Dsp()
	: PluginDef() {
	version = PLUGINDEF_VERSION;
	flags = 0;
	id = "eqs";
	name = N_("Scaleable EQ");
	groups = 0;
	description = ""; // description (tooltip)
	category = N_("Tone Control");       // category
	shortname = "";     // shortname
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
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<2; i++) fRec10[i] = 0;
	for (int i=0; i<2; i++) fRec12[i] = 0;
	for (int i=0; i<2; i++) fRec14[i] = 0;
	for (int i=0; i<2; i++) fRec16[i] = 0;
	for (int i=0; i<2; i++) fRec18[i] = 0;
	for (int i=0; i<3; i++) fRec19[i] = 0;
	for (int i=0; i<3; i++) fRec17[i] = 0;
	for (int i=0; i<3; i++) fRec15[i] = 0;
	for (int i=0; i<3; i++) fRec13[i] = 0;
	for (int i=0; i<3; i++) fRec11[i] = 0;
	for (int i=0; i<3; i++) fRec9[i] = 0;
	for (int i=0; i<3; i++) fRec7[i] = 0;
	for (int i=0; i<3; i++) fRec5[i] = 0;
	for (int i=0; i<3; i++) fRec3[i] = 0;
	for (int i=0; i<3; i++) fRec1[i] = 0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = (3.141592653589793 / double(min(192000, max(1, fSamplingFreq))));
	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	double 	fSlow0 = (0.0010000000000000009 * pow(10,(0.05 * double(fslider0))));
	double 	fSlow1 = (1.0 / double(fslider1));
	double 	fSlow2 = tan((fConst0 * double(fslider2)));
	double 	fSlow3 = (2 * (faustpower<2>(fSlow2) - 1));
	double 	fSlow4 = (0.0010000000000000009 * pow(10,(0.05 * double(fslider3))));
	double 	fSlow5 = (1.0 / double(fslider4));
	double 	fSlow6 = tan((fConst0 * double(fslider5)));
	double 	fSlow7 = (2 * (faustpower<2>(fSlow6) - 1));
	double 	fSlow8 = (0.0010000000000000009 * pow(10,(0.05 * double(fslider6))));
	double 	fSlow9 = (1.0 / double(fslider7));
	double 	fSlow10 = tan((fConst0 * double(fslider8)));
	double 	fSlow11 = (2 * (faustpower<2>(fSlow10) - 1));
	double 	fSlow12 = (0.0010000000000000009 * pow(10,(0.05 * double(fslider9))));
	double 	fSlow13 = (1.0 / double(fslider10));
	double 	fSlow14 = tan((fConst0 * double(fslider11)));
	double 	fSlow15 = (2 * (faustpower<2>(fSlow14) - 1));
	double 	fSlow16 = (0.0010000000000000009 * pow(10,(0.05 * double(fslider12))));
	double 	fSlow17 = (1.0 / double(fslider13));
	double 	fSlow18 = tan((fConst0 * double(fslider14)));
	double 	fSlow19 = (2 * (faustpower<2>(fSlow18) - 1));
	double 	fSlow20 = (0.0010000000000000009 * pow(10,(0.05 * double(fslider15))));
	double 	fSlow21 = (1.0 / double(fslider16));
	double 	fSlow22 = tan((fConst0 * double(fslider17)));
	double 	fSlow23 = (2 * (faustpower<2>(fSlow22) - 1));
	double 	fSlow24 = (0.0010000000000000009 * pow(10,(0.05 * double(fslider18))));
	double 	fSlow25 = (1.0 / double(fslider19));
	double 	fSlow26 = tan((fConst0 * double(fslider20)));
	double 	fSlow27 = (2 * (faustpower<2>(fSlow26) - 1));
	double 	fSlow28 = (0.0010000000000000009 * pow(10,(0.05 * double(fslider21))));
	double 	fSlow29 = (1.0 / double(fslider22));
	double 	fSlow30 = tan((fConst0 * double(fslider23)));
	double 	fSlow31 = (2 * (faustpower<2>(fSlow30) - 1));
	double 	fSlow32 = (0.0010000000000000009 * pow(10,(0.05 * double(fslider24))));
	double 	fSlow33 = (1.0 / double(fslider25));
	double 	fSlow34 = tan((fConst0 * double(fslider26)));
	double 	fSlow35 = (2 * (faustpower<2>(fSlow34) - 1));
	double 	fSlow36 = (0.0010000000000000009 * pow(10,(0.05 * double(fslider27))));
	double 	fSlow37 = (1.0 / double(fslider28));
	double 	fSlow38 = tan((fConst0 * double(fslider29)));
	double 	fSlow39 = (2 * (faustpower<2>(fSlow38) - 1));
	double 	fSlow40 = (1 + (fSlow38 * (fSlow38 - fSlow37)));
	double 	fSlow41 = (1 + (fSlow38 * (fSlow38 + fSlow37)));
	double 	fSlow42 = (1 + (fSlow34 * (fSlow34 - fSlow33)));
	double 	fSlow43 = (1 + (fSlow34 * (fSlow34 + fSlow33)));
	double 	fSlow44 = (1 + (fSlow30 * (fSlow30 - fSlow29)));
	double 	fSlow45 = (1 + (fSlow30 * (fSlow30 + fSlow29)));
	double 	fSlow46 = (1 + (fSlow26 * (fSlow26 - fSlow25)));
	double 	fSlow47 = (1 + (fSlow26 * (fSlow26 + fSlow25)));
	double 	fSlow48 = (1 + (fSlow22 * (fSlow22 - fSlow21)));
	double 	fSlow49 = (1 + (fSlow22 * (fSlow22 + fSlow21)));
	double 	fSlow50 = (1 + (fSlow18 * (fSlow18 - fSlow17)));
	double 	fSlow51 = (1 + (fSlow18 * (fSlow18 + fSlow17)));
	double 	fSlow52 = (1 + (fSlow14 * (fSlow14 - fSlow13)));
	double 	fSlow53 = (1 + (fSlow14 * (fSlow14 + fSlow13)));
	double 	fSlow54 = (1 + (fSlow10 * (fSlow10 - fSlow9)));
	double 	fSlow55 = (1 + (fSlow10 * (fSlow10 + fSlow9)));
	double 	fSlow56 = (1 + (fSlow6 * (fSlow6 - fSlow5)));
	double 	fSlow57 = (1 + (fSlow6 * (fSlow6 + fSlow5)));
	double 	fSlow58 = (1 + (fSlow2 * (fSlow2 - fSlow1)));
	double 	fSlow59 = (1 + (fSlow2 * (fSlow2 + fSlow1)));
	for (int i=0; i<count; i++) {
		fRec0[0] = (fSlow0 + (0.999 * fRec0[1]));
		double fTemp0 = (fSlow1 / fRec0[0]);
		double fTemp1 = (1 + (fSlow2 * (fSlow2 + fTemp0)));
		double fTemp2 = (fSlow3 * fRec1[1]);
		fRec2[0] = (fSlow4 + (0.999 * fRec2[1]));
		double fTemp3 = (fSlow5 / fRec2[0]);
		double fTemp4 = (1 + (fSlow6 * (fSlow6 + fTemp3)));
		double fTemp5 = (fSlow7 * fRec3[1]);
		fRec4[0] = (fSlow8 + (0.999 * fRec4[1]));
		double fTemp6 = (fSlow9 / fRec4[0]);
		double fTemp7 = (1 + (fSlow10 * (fSlow10 + fTemp6)));
		double fTemp8 = (fSlow11 * fRec5[1]);
		fRec6[0] = (fSlow12 + (0.999 * fRec6[1]));
		double fTemp9 = (fSlow13 / fRec6[0]);
		double fTemp10 = (1 + (fSlow14 * (fSlow14 + fTemp9)));
		double fTemp11 = (fSlow15 * fRec7[1]);
		fRec8[0] = (fSlow16 + (0.999 * fRec8[1]));
		double fTemp12 = (fSlow17 / fRec8[0]);
		double fTemp13 = (1 + (fSlow18 * (fSlow18 + fTemp12)));
		double fTemp14 = (fSlow19 * fRec9[1]);
		fRec10[0] = (fSlow20 + (0.999 * fRec10[1]));
		double fTemp15 = (fSlow21 / fRec10[0]);
		double fTemp16 = (1 + (fSlow22 * (fSlow22 + fTemp15)));
		double fTemp17 = (fSlow23 * fRec11[1]);
		fRec12[0] = (fSlow24 + (0.999 * fRec12[1]));
		double fTemp18 = (fSlow25 / fRec12[0]);
		double fTemp19 = (1 + (fSlow26 * (fSlow26 + fTemp18)));
		double fTemp20 = (fSlow27 * fRec13[1]);
		fRec14[0] = (fSlow28 + (0.999 * fRec14[1]));
		double fTemp21 = (fSlow29 / fRec14[0]);
		double fTemp22 = (1 + (fSlow30 * (fSlow30 + fTemp21)));
		double fTemp23 = (fSlow31 * fRec15[1]);
		fRec16[0] = (fSlow32 + (0.999 * fRec16[1]));
		double fTemp24 = (fSlow33 / fRec16[0]);
		double fTemp25 = (1 + (fSlow34 * (fSlow34 + fTemp24)));
		double fTemp26 = (fSlow35 * fRec17[1]);
		fRec18[0] = (fSlow36 + (0.999 * fRec18[1]));
		double fTemp27 = (fSlow37 / fRec18[0]);
		double fTemp28 = (1 + (fSlow38 * (fSlow38 + fTemp27)));
		double fTemp29 = (fSlow39 * fRec19[1]);
		fRec19[0] = ((double)input0[i] - ((((1 + (fSlow38 * (fSlow38 - fTemp27))) * fRec19[2]) + fTemp29) / fTemp28));
		fRec17[0] = ((((fTemp29 + (fSlow41 * fRec19[0])) + (fSlow40 * fRec19[2])) / fTemp28) - ((((1 + (fSlow34 * (fSlow34 - fTemp24))) * fRec17[2]) + fTemp26) / fTemp25));
		fRec15[0] = ((((fTemp26 + (fSlow43 * fRec17[0])) + (fSlow42 * fRec17[2])) / fTemp25) - ((((1 + (fSlow30 * (fSlow30 - fTemp21))) * fRec15[2]) + fTemp23) / fTemp22));
		fRec13[0] = ((((fTemp23 + (fSlow45 * fRec15[0])) + (fSlow44 * fRec15[2])) / fTemp22) - ((((1 + (fSlow26 * (fSlow26 - fTemp18))) * fRec13[2]) + fTemp20) / fTemp19));
		fRec11[0] = ((((fTemp20 + (fSlow47 * fRec13[0])) + (fSlow46 * fRec13[2])) / fTemp19) - ((((1 + (fSlow22 * (fSlow22 - fTemp15))) * fRec11[2]) + fTemp17) / fTemp16));
		fRec9[0] = ((((fTemp17 + (fSlow49 * fRec11[0])) + (fSlow48 * fRec11[2])) / fTemp16) - ((((1 + (fSlow18 * (fSlow18 - fTemp12))) * fRec9[2]) + fTemp14) / fTemp13));
		fRec7[0] = ((((fTemp14 + (fSlow51 * fRec9[0])) + (fSlow50 * fRec9[2])) / fTemp13) - ((((1 + (fSlow14 * (fSlow14 - fTemp9))) * fRec7[2]) + fTemp11) / fTemp10));
		fRec5[0] = ((((fTemp11 + (fSlow53 * fRec7[0])) + (fSlow52 * fRec7[2])) / fTemp10) - ((((1 + (fSlow10 * (fSlow10 - fTemp6))) * fRec5[2]) + fTemp8) / fTemp7));
		fRec3[0] = ((((fTemp8 + (fSlow55 * fRec5[0])) + (fSlow54 * fRec5[2])) / fTemp7) - ((((1 + (fSlow6 * (fSlow6 - fTemp3))) * fRec3[2]) + fTemp5) / fTemp4));
		fRec1[0] = ((((fTemp5 + (fSlow57 * fRec3[0])) + (fSlow56 * fRec3[2])) / fTemp4) - ((((1 + (fSlow2 * (fSlow2 - fTemp0))) * fRec1[2]) + fTemp2) / fTemp1));
		output0[i] = (FAUSTFLOAT)(((fTemp2 + (fSlow59 * fRec1[0])) + (fSlow58 * fRec1[2])) / fTemp1);
		// post processing
		fRec1[2] = fRec1[1]; fRec1[1] = fRec1[0];
		fRec3[2] = fRec3[1]; fRec3[1] = fRec3[0];
		fRec5[2] = fRec5[1]; fRec5[1] = fRec5[0];
		fRec7[2] = fRec7[1]; fRec7[1] = fRec7[0];
		fRec9[2] = fRec9[1]; fRec9[1] = fRec9[0];
		fRec11[2] = fRec11[1]; fRec11[1] = fRec11[0];
		fRec13[2] = fRec13[1]; fRec13[1] = fRec13[0];
		fRec15[2] = fRec15[1]; fRec15[1] = fRec15[0];
		fRec17[2] = fRec17[1]; fRec17[1] = fRec17[0];
		fRec19[2] = fRec19[1]; fRec19[1] = fRec19[0];
		fRec18[1] = fRec18[0];
		fRec16[1] = fRec16[0];
		fRec14[1] = fRec14[0];
		fRec12[1] = fRec12[0];
		fRec10[1] = fRec10[0];
		fRec8[1] = fRec8[0];
		fRec6[1] = fRec6[0];
		fRec4[1] = fRec4[0];
		fRec2[1] = fRec2[0];
		fRec0[1] = fRec0[0];
	}
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerVar("eqs.Qs125","","S",N_("bandwidth"),&fslider22, 5e+01, 1.0, 1e+02, 1.0);
	reg.registerVar("eqs.Qs16k","","S","",&fslider1, 5e+01, 1.0, 1e+02, 1.0);
	reg.registerVar("eqs.Qs1k","","S",N_("bandwidth"),&fslider13, 5e+01, 1.0, 1e+02, 1.0);
	reg.registerVar("eqs.Qs250","","S",N_("bandwidth"),&fslider19, 5e+01, 1.0, 1e+02, 1.0);
	reg.registerVar("eqs.Qs2k","","S",N_("bandwidth"),&fslider10, 5e+01, 1.0, 1e+02, 1.0);
	reg.registerVar("eqs.Qs31_25","","S",N_("bandwidth"),&fslider28, 5e+01, 1.0, 1e+02, 1.0);
	reg.registerVar("eqs.Qs4k","","S","",&fslider7, 5e+01, 1.0, 1e+02, 1.0);
	reg.registerVar("eqs.Qs500","","S",N_("bandwidth"),&fslider16, 5e+01, 1.0, 1e+02, 1.0);
	reg.registerVar("eqs.Qs62_5","","S",N_("bandwidth"),&fslider25, 5e+01, 1.0, 1e+02, 1.0);
	reg.registerVar("eqs.Qs8k","","S","",&fslider4, 5e+01, 1.0, 1e+02, 1.0);
	reg.registerVar("eqs.freq125","","S",N_("Hz"),&fslider23, 125.0, 2e+01, 2e+04, 1.0);
	reg.registerVar("eqs.freq16k","","S",N_("Hz"),&fslider2, 1.6e+04, 2e+01, 2e+04, 1.0);
	reg.registerVar("eqs.freq1k","","S",N_("Hz"),&fslider14, 1e+03, 2e+01, 2e+04, 1.0);
	reg.registerVar("eqs.freq250","","S",N_("Hz"),&fslider20, 2.5e+02, 2e+01, 2e+04, 1.0);
	reg.registerVar("eqs.freq2k","","S",N_("Hz"),&fslider11, 2e+03, 2e+01, 2e+04, 1.0);
	reg.registerVar("eqs.freq31_25","","S",N_("Hz"),&fslider29, 31.25, 2e+01, 2e+04, 1.0);
	reg.registerVar("eqs.freq4k","","S",N_("Hz"),&fslider8, 4e+03, 2e+01, 2e+04, 1.0);
	reg.registerVar("eqs.freq500","","S",N_("Hz"),&fslider17, 5e+02, 2e+01, 2e+04, 1.0);
	reg.registerVar("eqs.freq62_5","","S",N_("Hz"),&fslider26, 62.5, 2e+01, 2e+04, 1.0);
	reg.registerVar("eqs.freq8k","","S",N_("Hz"),&fslider5, 8e+03, 2e+01, 2e+04, 1.0);
	reg.registerVar("eqs.fs125","","S",N_("gain (dB) at 125 Hz"),&fslider21, 0.0, -4e+01, 3e+01, 0.1);
	reg.registerVar("eqs.fs16k","","S",N_("gain (dB) at 16 kHz"),&fslider0, 0.0, -4e+01, 3e+01, 0.1);
	reg.registerVar("eqs.fs1k","","S",N_("gain (dB) at 1 kHz"),&fslider12, 0.0, -4e+01, 3e+01, 0.1);
	reg.registerVar("eqs.fs250","","S",N_("gain (dB) at 250 Hz"),&fslider18, 0.0, -4e+01, 3e+01, 0.1);
	reg.registerVar("eqs.fs2k","","S",N_("gain (dB) at 2 kHz"),&fslider9, 0.0, -4e+01, 3e+01, 0.1);
	reg.registerVar("eqs.fs31_25","","S",N_("gain (dB) at 31.25 Hz"),&fslider27, 0.0, -4e+01, 3e+01, 0.1);
	reg.registerVar("eqs.fs4k","","S",N_("gain (dB) at 4 kHz"),&fslider6, 0.0, -4e+01, 3e+01, 0.1);
	reg.registerVar("eqs.fs500","","S",N_("gain (dB) at 500 Hz"),&fslider15, 0.0, -4e+01, 3e+01, 0.1);
	reg.registerVar("eqs.fs62_5","","S",N_("gain (dB) at 62.5 Hz"),&fslider24, 0.0, -4e+01, 3e+01, 0.1);
	reg.registerVar("eqs.fs8k","","S",N_("gain (dB) at 8 kHz"),&fslider3, 0.0, -4e+01, 3e+01, 0.1);
	return 0;
}

int Dsp::register_params_static(const ParamReg& reg)
{
	return static_cast<Dsp*>(reg.plugin)->register_par(reg);
}

const char *Dsp::glade_def = "\
<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n\
<interface>\n\
  <!-- interface-requires gxwidgets 0.0 -->\n\
  <requires lib=\"gtk+\" version=\"2.20\"/>\n\
  <!-- interface-naming-policy project-wide -->\n\
  <object class=\"GtkWindow\" id=\"window1\">\n\
    <property name=\"can_focus\">False</property>\n\
    <child>\n\
      <object class=\"GtkVBox\" id=\"vbox1\">\n\
        <property name=\"visible\">True</property>\n\
        <property name=\"can_focus\">False</property>\n\
        <child>\n\
          <object class=\"GxPaintBox\" id=\"rackbox\">\n\
            <property name=\"visible\">True</property>\n\
            <property name=\"can_focus\">False</property>\n\
            <property name=\"spacing\">4</property>\n\
            <property name=\"paint_func\">box_uni_2_expose</property>\n\
            <child>\n\
              <object class=\"GtkTable\" id=\"table1\">\n\
                <property name=\"visible\">True</property>\n\
                <property name=\"can_focus\">False</property>\n\
                <property name=\"n_rows\">3</property>\n\
                <property name=\"n_columns\">10</property>\n\
                <property name=\"column_spacing\">3</property>\n\
                <property name=\"row_spacing\">10</property>\n\
                <child>\n\
                  <object class=\"GtkVBox\" id=\"vbox2\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                    <property name=\"spacing\">5</property>\n\
                    <child>\n\
                      <object class=\"GtkLabel\" id=\"label1:rack_label_inverse\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"label\" translatable=\"yes\">Q</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">0</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GxSmallKnob\" id=\"gxbigknob1\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">True</property>\n\
                        <property name=\"receives_default\">True</property>\n\
                        <property name=\"var_id\">eqs.Qs31_25</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">1</property>\n\
                      </packing>\n\
                    </child>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"top_attach\">2</property>\n\
                    <property name=\"bottom_attach\">3</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GtkVBox\" id=\"vbox3\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                    <property name=\"spacing\">5</property>\n\
                    <child>\n\
                      <object class=\"GtkLabel\" id=\"label2:rack_label_inverse\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"label\" translatable=\"yes\">Q</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">0</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GxSmallKnob\" id=\"gxbigknob2\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">True</property>\n\
                        <property name=\"receives_default\">True</property>\n\
                        <property name=\"var_id\">eqs.Qs62_5</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">1</property>\n\
                      </packing>\n\
                    </child>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"left_attach\">1</property>\n\
                    <property name=\"right_attach\">2</property>\n\
                    <property name=\"top_attach\">2</property>\n\
                    <property name=\"bottom_attach\">3</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GtkVBox\" id=\"vbox4\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                    <property name=\"spacing\">5</property>\n\
                    <child>\n\
                      <object class=\"GtkLabel\" id=\"label3:rack_label_inverse\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"label\" translatable=\"yes\">Q</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">0</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GxSmallKnob\" id=\"gxbigknob3\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">True</property>\n\
                        <property name=\"receives_default\">True</property>\n\
                        <property name=\"var_id\">eqs.Qs125</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">1</property>\n\
                      </packing>\n\
                    </child>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"left_attach\">2</property>\n\
                    <property name=\"right_attach\">3</property>\n\
                    <property name=\"top_attach\">2</property>\n\
                    <property name=\"bottom_attach\">3</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GtkVBox\" id=\"vbox5\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                    <property name=\"spacing\">5</property>\n\
                    <child>\n\
                      <object class=\"GtkLabel\" id=\"label4:rack_label_inverse\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"label\" translatable=\"yes\">Q</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">0</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GxSmallKnob\" id=\"gxbigknob4\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">True</property>\n\
                        <property name=\"receives_default\">True</property>\n\
                        <property name=\"var_id\">eqs.Qs250</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">1</property>\n\
                      </packing>\n\
                    </child>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"left_attach\">3</property>\n\
                    <property name=\"right_attach\">4</property>\n\
                    <property name=\"top_attach\">2</property>\n\
                    <property name=\"bottom_attach\">3</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GtkVBox\" id=\"vbox6\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                    <property name=\"spacing\">5</property>\n\
                    <child>\n\
                      <object class=\"GtkLabel\" id=\"label5:rack_label_inverse\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"label\" translatable=\"yes\">Q</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">0</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GxSmallKnob\" id=\"gxbigknob5\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">True</property>\n\
                        <property name=\"receives_default\">True</property>\n\
                        <property name=\"var_id\">eqs.Qs500</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">1</property>\n\
                      </packing>\n\
                    </child>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"left_attach\">4</property>\n\
                    <property name=\"right_attach\">5</property>\n\
                    <property name=\"top_attach\">2</property>\n\
                    <property name=\"bottom_attach\">3</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GtkVBox\" id=\"vbox7\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                    <property name=\"spacing\">5</property>\n\
                    <child>\n\
                      <object class=\"GtkLabel\" id=\"label6:rack_label_inverse\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"label\" translatable=\"yes\">Q</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">0</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GxSmallKnob\" id=\"gxbigknob6\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">True</property>\n\
                        <property name=\"receives_default\">True</property>\n\
                        <property name=\"var_id\">eqs.Qs1k</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">1</property>\n\
                      </packing>\n\
                    </child>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"left_attach\">5</property>\n\
                    <property name=\"right_attach\">6</property>\n\
                    <property name=\"top_attach\">2</property>\n\
                    <property name=\"bottom_attach\">3</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GtkVBox\" id=\"vbox8\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                    <property name=\"spacing\">5</property>\n\
                    <child>\n\
                      <object class=\"GtkLabel\" id=\"label7:rack_label_inverse\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"label\" translatable=\"yes\">Q</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">0</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GxSmallKnob\" id=\"gxbigknob7\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">True</property>\n\
                        <property name=\"receives_default\">True</property>\n\
                        <property name=\"var_id\">eqs.Qs2k</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">1</property>\n\
                      </packing>\n\
                    </child>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"left_attach\">6</property>\n\
                    <property name=\"right_attach\">7</property>\n\
                    <property name=\"top_attach\">2</property>\n\
                    <property name=\"bottom_attach\">3</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GtkVBox\" id=\"vbox9\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                    <property name=\"spacing\">5</property>\n\
                    <child>\n\
                      <object class=\"GtkLabel\" id=\"label8:rack_label_inverse\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"label\" translatable=\"yes\">Q</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">0</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GxSmallKnob\" id=\"gxbigknob8\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">True</property>\n\
                        <property name=\"receives_default\">True</property>\n\
                        <property name=\"var_id\">eqs.Qs4k</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">1</property>\n\
                      </packing>\n\
                    </child>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"left_attach\">7</property>\n\
                    <property name=\"right_attach\">8</property>\n\
                    <property name=\"top_attach\">2</property>\n\
                    <property name=\"bottom_attach\">3</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GtkVBox\" id=\"vbox10\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                    <property name=\"spacing\">5</property>\n\
                    <child>\n\
                      <object class=\"GtkLabel\" id=\"label9:rack_label_inverse\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"label\" translatable=\"yes\">Q</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">0</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GxSmallKnob\" id=\"gxbigknob9\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">True</property>\n\
                        <property name=\"receives_default\">True</property>\n\
                        <property name=\"var_id\">eqs.Qs8k</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">1</property>\n\
                      </packing>\n\
                    </child>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"left_attach\">8</property>\n\
                    <property name=\"right_attach\">9</property>\n\
                    <property name=\"top_attach\">2</property>\n\
                    <property name=\"bottom_attach\">3</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GtkVBox\" id=\"vbox11\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                    <property name=\"spacing\">5</property>\n\
                    <child>\n\
                      <object class=\"GtkLabel\" id=\"label10:rack_label_inverse\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"label\" translatable=\"yes\">Q</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">0</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GxSmallKnob\" id=\"gxbigknob10\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">True</property>\n\
                        <property name=\"receives_default\">True</property>\n\
                        <property name=\"var_id\">eqs.Qs16k</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">1</property>\n\
                      </packing>\n\
                    </child>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"left_attach\">9</property>\n\
                    <property name=\"right_attach\">10</property>\n\
                    <property name=\"top_attach\">2</property>\n\
                    <property name=\"bottom_attach\">3</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GxVSlider\" id=\"gxvslider1\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">True</property>\n\
                    <property name=\"receives_default\">True</property>\n\
                    <property name=\"var_id\">eqs.fs31_25</property>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"top_attach\">1</property>\n\
                    <property name=\"bottom_attach\">2</property>\n\
                    <property name=\"x_options\">GTK_EXPAND</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GxVSlider\" id=\"gxvslider2\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">True</property>\n\
                    <property name=\"receives_default\">True</property>\n\
                    <property name=\"var_id\">eqs.fs62_5</property>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"left_attach\">1</property>\n\
                    <property name=\"right_attach\">2</property>\n\
                    <property name=\"top_attach\">1</property>\n\
                    <property name=\"bottom_attach\">2</property>\n\
                    <property name=\"x_options\">GTK_EXPAND</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GxVSlider\" id=\"gxvslider3\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">True</property>\n\
                    <property name=\"receives_default\">True</property>\n\
                    <property name=\"var_id\">eqs.fs125</property>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"left_attach\">2</property>\n\
                    <property name=\"right_attach\">3</property>\n\
                    <property name=\"top_attach\">1</property>\n\
                    <property name=\"bottom_attach\">2</property>\n\
                    <property name=\"x_options\">GTK_EXPAND</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GxVSlider\" id=\"gxvslider4\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">True</property>\n\
                    <property name=\"receives_default\">True</property>\n\
                    <property name=\"var_id\">eqs.fs250</property>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"left_attach\">3</property>\n\
                    <property name=\"right_attach\">4</property>\n\
                    <property name=\"top_attach\">1</property>\n\
                    <property name=\"bottom_attach\">2</property>\n\
                    <property name=\"x_options\">GTK_EXPAND</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GxVSlider\" id=\"gxvslider5\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">True</property>\n\
                    <property name=\"receives_default\">True</property>\n\
                    <property name=\"var_id\">eqs.fs500</property>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"left_attach\">4</property>\n\
                    <property name=\"right_attach\">5</property>\n\
                    <property name=\"top_attach\">1</property>\n\
                    <property name=\"bottom_attach\">2</property>\n\
                    <property name=\"x_options\">GTK_EXPAND</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GxVSlider\" id=\"gxvslider6\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">True</property>\n\
                    <property name=\"receives_default\">True</property>\n\
                    <property name=\"var_id\">eqs.fs1k</property>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"left_attach\">5</property>\n\
                    <property name=\"right_attach\">6</property>\n\
                    <property name=\"top_attach\">1</property>\n\
                    <property name=\"bottom_attach\">2</property>\n\
                    <property name=\"x_options\">GTK_EXPAND</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GxVSlider\" id=\"gxvslider7\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">True</property>\n\
                    <property name=\"receives_default\">True</property>\n\
                    <property name=\"var_id\">eqs.fs2k</property>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"left_attach\">6</property>\n\
                    <property name=\"right_attach\">7</property>\n\
                    <property name=\"top_attach\">1</property>\n\
                    <property name=\"bottom_attach\">2</property>\n\
                    <property name=\"x_options\">GTK_EXPAND</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GxVSlider\" id=\"gxvslider8\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">True</property>\n\
                    <property name=\"receives_default\">True</property>\n\
                    <property name=\"var_id\">eqs.fs4k</property>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"left_attach\">7</property>\n\
                    <property name=\"right_attach\">8</property>\n\
                    <property name=\"top_attach\">1</property>\n\
                    <property name=\"bottom_attach\">2</property>\n\
                    <property name=\"x_options\">GTK_EXPAND</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GxVSlider\" id=\"gxvslider9\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">True</property>\n\
                    <property name=\"receives_default\">True</property>\n\
                    <property name=\"var_id\">eqs.fs8k</property>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"left_attach\">8</property>\n\
                    <property name=\"right_attach\">9</property>\n\
                    <property name=\"top_attach\">1</property>\n\
                    <property name=\"bottom_attach\">2</property>\n\
                    <property name=\"x_options\">GTK_EXPAND</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GxVSlider\" id=\"gxvslider10\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">True</property>\n\
                    <property name=\"receives_default\">True</property>\n\
                    <property name=\"var_id\">eqs.fs16k</property>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"left_attach\">9</property>\n\
                    <property name=\"right_attach\">10</property>\n\
                    <property name=\"top_attach\">1</property>\n\
                    <property name=\"bottom_attach\">2</property>\n\
                    <property name=\"x_options\">GTK_EXPAND</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GxValueDisplay\" id=\"gxvaluedisplay1\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">True</property>\n\
                    <property name=\"receives_default\">True</property>\n\
                    <property name=\"var_id\">eqs.freq31_25</property>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"x_options\"/>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GxValueDisplay\" id=\"gxvaluedisplay2\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">True</property>\n\
                    <property name=\"receives_default\">True</property>\n\
                    <property name=\"var_id\">eqs.freq62_5</property>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"left_attach\">1</property>\n\
                    <property name=\"right_attach\">2</property>\n\
                    <property name=\"x_options\"/>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GxValueDisplay\" id=\"gxvaluedisplay3\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">True</property>\n\
                    <property name=\"receives_default\">True</property>\n\
                    <property name=\"var_id\">eqs.freq125</property>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"left_attach\">2</property>\n\
                    <property name=\"right_attach\">3</property>\n\
                    <property name=\"x_options\"/>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GxValueDisplay\" id=\"gxvaluedisplay4\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">True</property>\n\
                    <property name=\"receives_default\">True</property>\n\
                    <property name=\"var_id\">eqs.freq250</property>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"left_attach\">3</property>\n\
                    <property name=\"right_attach\">4</property>\n\
                    <property name=\"x_options\"/>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GxValueDisplay\" id=\"gxvaluedisplay5\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">True</property>\n\
                    <property name=\"receives_default\">True</property>\n\
                    <property name=\"var_id\">eqs.freq500</property>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"left_attach\">4</property>\n\
                    <property name=\"right_attach\">5</property>\n\
                    <property name=\"x_options\"/>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GxValueDisplay\" id=\"gxvaluedisplay6\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">True</property>\n\
                    <property name=\"receives_default\">True</property>\n\
                    <property name=\"var_id\">eqs.freq1k</property>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"left_attach\">5</property>\n\
                    <property name=\"right_attach\">6</property>\n\
                    <property name=\"x_options\"/>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GxValueDisplay\" id=\"gxvaluedisplay7\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">True</property>\n\
                    <property name=\"receives_default\">True</property>\n\
                    <property name=\"var_id\">eqs.freq2k</property>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"left_attach\">6</property>\n\
                    <property name=\"right_attach\">7</property>\n\
                    <property name=\"x_options\"/>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GxValueDisplay\" id=\"gxvaluedisplay8\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">True</property>\n\
                    <property name=\"receives_default\">True</property>\n\
                    <property name=\"var_id\">eqs.freq4k</property>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"left_attach\">7</property>\n\
                    <property name=\"right_attach\">8</property>\n\
                    <property name=\"x_options\"/>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GxValueDisplay\" id=\"gxvaluedisplay9\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">True</property>\n\
                    <property name=\"receives_default\">True</property>\n\
                    <property name=\"var_id\">eqs.freq8k</property>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"left_attach\">8</property>\n\
                    <property name=\"right_attach\">9</property>\n\
                    <property name=\"x_options\"/>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GxValueDisplay\" id=\"gxvaluedisplay10\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">True</property>\n\
                    <property name=\"receives_default\">True</property>\n\
                    <property name=\"var_id\">eqs.freq16k</property>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"left_attach\">9</property>\n\
                    <property name=\"right_attach\">10</property>\n\
                    <property name=\"x_options\"/>\n\
                  </packing>\n\
                </child>\n\
              </object>\n\
              <packing>\n\
                <property name=\"expand\">True</property>\n\
                <property name=\"fill\">True</property>\n\
                <property name=\"position\">0</property>\n\
              </packing>\n\
            </child>\n\
          </object>\n\
          <packing>\n\
            <property name=\"expand\">True</property>\n\
            <property name=\"fill\">False</property>\n\
            <property name=\"position\">0</property>\n\
          </packing>\n\
        </child>\n\
        <child>\n\
          <object class=\"GtkHBox\" id=\"minibox\">\n\
            <property name=\"visible\">True</property>\n\
            <property name=\"can_focus\">False</property>\n\
            <property name=\"spacing\">4</property>\n\
            <child>\n\
              <placeholder/>\n\
            </child>\n\
            <child>\n\
              <placeholder/>\n\
            </child>\n\
          </object>\n\
          <packing>\n\
            <property name=\"expand\">True</property>\n\
            <property name=\"fill\">True</property>\n\
            <property name=\"position\">1</property>\n\
          </packing>\n\
        </child>\n\
      </object>\n\
    </child>\n\
  </object>\n\
</interface>\n\
";

inline int Dsp::load_ui_f(const UiBuilder& b, int form)
{
    if (form & UI_FORM_GLADE) {
        b.load_glade(glade_def);
        return 0;
    }
    if (form & UI_FORM_STACK) {
#define PARAM(p) ("eqs" "." p)
// EQ
b.openHorizontalhideBox("");
b.closeBox();
b.openVerticalBox("");
{
    b.openHorizontalTableBox("");
    {
	b.create_simple_spin_value("eqs.freq31_25");
	b.create_simple_spin_value("eqs.freq62_5");
	b.create_simple_spin_value("eqs.freq125");
	b.create_simple_spin_value("eqs.freq250");
	b.create_simple_spin_value("eqs.freq500");
	b.create_simple_spin_value("eqs.freq1k");
	b.create_simple_spin_value("eqs.freq2k");
	b.create_simple_spin_value("eqs.freq4k");
	b.create_simple_spin_value("eqs.freq8k");
	b.create_simple_spin_value("eqs.freq16k");
    }
    b.closeBox();
    b.openHorizontalTableBox("");
    {
	b.create_eq_rackslider_no_caption("eqs.fs31_25");
	b.create_eq_rackslider_no_caption("eqs.fs62_5");
	b.create_eq_rackslider_no_caption("eqs.fs125");
	b.create_eq_rackslider_no_caption("eqs.fs250");
	b.create_eq_rackslider_no_caption("eqs.fs500");
	b.create_eq_rackslider_no_caption("eqs.fs1k");
	b.create_eq_rackslider_no_caption("eqs.fs2k");
	b.create_eq_rackslider_no_caption("eqs.fs4k");
	b.create_eq_rackslider_no_caption("eqs.fs8k");
	b.create_eq_rackslider_no_caption("eqs.fs16k");
    }
    b.closeBox();
    b.openHorizontalTableBox("");
    {
	b.create_small_rackknob("eqs.Qs31_25", "Q");
	b.create_small_rackknob("eqs.Qs62_5", "Q");
	b.create_small_rackknob("eqs.Qs125", "Q");
	b.create_small_rackknob("eqs.Qs250", "Q");
	b.create_small_rackknob("eqs.Qs500", "Q");
	b.create_small_rackknob("eqs.Qs1k", "Q");
	b.create_small_rackknob("eqs.Qs2k", "Q");
	b.create_small_rackknob("eqs.Qs4k", "Q");
	b.create_small_rackknob("eqs.Qs8k", "Q");
	b.create_small_rackknob("eqs.Qs16k", "Q");
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

} // end namespace selecteq
