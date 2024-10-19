// generated from file '../src/faust/rolwah.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)


namespace rolwah {

class Dsp: public PluginDef {
private:
	int fSampleRate;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	int iVec0[2];
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	double fConst0;
	double fConst1;
	double fRec2[2];
	double fRec1[2];
	double fRec0[2];
	double fConst2;
	double fConst3;
	double fConst4;
	double fRec5[2];
	double fConst5;
	double fRec4[2];
	double fRec3[2];
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT	*fVslider2_;
	double fRec6[2];
	double fConst6;
	double fConst7;
	double fConst8;
	double fConst9;
	double fConst10;
	double fConst11;
	double fConst12;
	double fConst13;
	double fConst14;
	double fConst15;
	double fConst16;
	double fConst17;
	double fConst18;
	double fConst19;
	double fConst20;
	double fConst21;
	double fConst22;
	double fConst23;
	double fConst24;
	double fConst25;
	double fConst26;
	double fConst27;
	double fConst28;
	double fConst29;
	double fConst30;
	double fConst31;
	double fConst32;
	double fConst33;
	double fConst34;
	FAUSTFLOAT fVslider3;
	FAUSTFLOAT	*fVslider3_;
	double fConst35;
	double fConst36;
	double fConst37;
	double fVec1[2];
	double fConst38;
	double fConst39;
	double fRec8[2];
	double fRec7[5];
	double fConst40;
	double fConst41;
	double fConst42;
	double fConst43;
	double fConst44;
	double fConst45;
	double fConst46;
	double fConst47;
	double fConst48;
	double fConst49;
	double fConst50;
	double fConst51;
	double fConst52;
	double fConst53;
	double fConst54;

	void clear_state_f();
	void init(unsigned int sample_rate);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0);
	int register_par(const ParamReg& reg);

	static void clear_state_f_static(PluginDef*);
	static void init_static(unsigned int sample_rate, PluginDef*);
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
	id = "rolwah";
	name = N_("Roland Wah");
	groups = 0;
	description = N_("Roland Wah"); // description (tooltip)
	category = N_("Guitar Effects");       // category
	shortname = "";     // shortname
	mono_audio = compute_static;
	stereo_audio = 0;
	set_samplerate = init_static;
	activate_plugin = 0;
	register_params = register_params_static;
	load_ui = 0;
	clear_state = clear_state_f_static;
	delete_instance = del_instance;
}

Dsp::~Dsp() {
}

inline void Dsp::clear_state_f()
{
	for (int l0 = 0; l0 < 2; l0 = l0 + 1) iVec0[l0] = 0;
	for (int l1 = 0; l1 < 2; l1 = l1 + 1) fRec2[l1] = 0.0;
	for (int l2 = 0; l2 < 2; l2 = l2 + 1) fRec1[l2] = 0.0;
	for (int l3 = 0; l3 < 2; l3 = l3 + 1) fRec0[l3] = 0.0;
	for (int l4 = 0; l4 < 2; l4 = l4 + 1) fRec5[l4] = 0.0;
	for (int l5 = 0; l5 < 2; l5 = l5 + 1) fRec4[l5] = 0.0;
	for (int l6 = 0; l6 < 2; l6 = l6 + 1) fRec3[l6] = 0.0;
	for (int l7 = 0; l7 < 2; l7 = l7 + 1) fRec6[l7] = 0.0;
	for (int l8 = 0; l8 < 2; l8 = l8 + 1) fVec1[l8] = 0.0;
	for (int l9 = 0; l9 < 2; l9 = l9 + 1) fRec8[l9] = 0.0;
	for (int l10 = 0; l10 < 5; l10 = l10 + 1) fRec7[l10] = 0.0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int sample_rate)
{
	fSampleRate = sample_rate;
	fConst0 = std::min<double>(1.92e+05, std::max<double>(1.0, double(fSampleRate)));
	fConst1 = 0.10471975511965977 / fConst0;
	fConst2 = std::exp(-(1e+02 / fConst0));
	fConst3 = std::exp(-(1e+01 / fConst0));
	fConst4 = 1.0 - fConst3;
	fConst5 = 1.0 - fConst2;
	fConst6 = 1.00220281601996e-19 * fConst0;
	fConst7 = mydsp_faustpower2_f(fConst0);
	fConst8 = fConst7 * (fConst0 * (-1.70950590451549e-17 - fConst6) + -1.90549124429613e-13);
	fConst9 = 4.01507415376654e-19 * fConst0;
	fConst10 = fConst0 * (fConst0 * (fConst0 * (fConst9 + 3.69834165265026e-17) + 1.74041670594569e-13) + 2.88710794590323e-12);
	fConst11 = 1.17381624550525e-20 * fConst0;
	fConst12 = fConst0 * (fConst0 * (fConst0 * (fConst11 + 1.80001288492797e-17) + 5.87277230952925e-13) + 1.11753192188666e-11);
	fConst13 = 6.69695568374064e-21 * fConst0;
	fConst14 = mydsp_faustpower3_f(fConst0);
	fConst15 = fConst14 * (5.68713395403691e-17 - fConst13);
	fConst16 = 6.68344015946305e-21 * fConst0;
	fConst17 = fConst0 * (fConst7 * (fConst16 + -5.68918771358741e-17) + 1.08157343487654e-12);
	fConst18 = 9.00669599516373e-21 * fConst0;
	fConst19 = fConst0 * (fConst7 * (fConst18 + -1.44001767611744e-16) + 1.27820700067781e-12);
	fConst20 = fConst7 * (fConst0 * (1.70950590451549e-17 - fConst6) + -1.90549124429613e-13);
	fConst21 = fConst0 * (fConst0 * (fConst0 * (fConst9 + -3.69834165265026e-17) + 1.74041670594569e-13) + -2.88710794590323e-12);
	fConst22 = fConst0 * (fConst0 * (fConst0 * (fConst11 + -1.80001288492797e-17) + 5.87277230952925e-13) + -1.11753192188666e-11);
	fConst23 = 4.00881126407982e-19 * fConst0;
	fConst24 = fConst14 * (fConst23 + -3.41901180903099e-17);
	fConst25 = 1.60602966150662e-18 * fConst0;
	fConst26 = fConst0 * (fConst7 * (7.39668330530053e-17 - fConst25) + -5.77421589180647e-12);
	fConst27 = 4.69526498202101e-20 * fConst0;
	fConst28 = fConst0 * (fConst7 * (3.60002576985594e-17 - fConst27) + -2.23506384377333e-11);
	fConst29 = 3.81098248859227e-13 - 6.01321689611973e-19 * fConst7;
	fConst30 = 2.40904449225993e-18 * fConst7 + -3.48083341189137e-13;
	fConst31 = 7.04289747303152e-20 * fConst7 + -1.17455446190585e-12;
	fConst32 = fConst14 * (fConst23 + 3.41901180903099e-17);
	fConst33 = fConst0 * (fConst7 * (-7.39668330530053e-17 - fConst25) + 5.77421589180647e-12);
	fConst34 = fConst0 * (fConst7 * (-3.60002576985594e-17 - fConst27) + 2.23506384377333e-11);
	fConst35 = 561.1941267851723 / fConst0;
	fConst36 = fConst35 + 1.0;
	fConst37 = 0.01 / fConst36;
	fConst38 = 1.0 - fConst35;
	fConst39 = 1.0 / fConst36;
	fConst40 = fConst14 * (-5.68713395403691e-17 - fConst13);
	fConst41 = fConst0 * (fConst7 * (fConst16 + 5.68918771358741e-17) + -1.08157343487654e-12);
	fConst42 = fConst0 * (fConst7 * (fConst18 + 1.44001767611744e-16) + -1.27820700067781e-12);
	fConst43 = 1.67423892093516e-21 * fConst0;
	fConst44 = fConst7 * (fConst0 * (fConst43 + 2.84356697701846e-17) + 4.21808310223676e-14);
	fConst45 = 1.67086003986576e-21 * fConst0;
	fConst46 = fConst0 * (fConst0 * (fConst0 * (-2.84459385679371e-17 - fConst45) + -4.25288501077712e-14) + -5.40786717438269e-13);
	fConst47 = 2.25167399879093e-21 * fConst0;
	fConst48 = fConst0 * (fConst0 * (fConst0 * (-7.2000883805872e-17 - fConst47) + -1.122655366476e-13) + -6.39103500338903e-13);
	fConst49 = fConst7 * (fConst0 * (fConst43 + -2.84356697701846e-17) + 4.21808310223676e-14);
	fConst50 = fConst0 * (fConst0 * (fConst0 * (2.84459385679371e-17 - fConst45) + -4.25288501077712e-14) + 5.40786717438269e-13);
	fConst51 = fConst0 * (fConst0 * (fConst0 * (7.2000883805872e-17 - fConst47) + -1.122655366476e-13) + 6.39103500338903e-13);
	fConst52 = 1.35100439927456e-20 * fConst7;
	fConst53 = 1.00251602391946e-20 * fConst7;
	fConst54 = 1.0045433525611e-20 * fConst7 + -8.43616620447352e-14;
	clear_state_f();
}

void Dsp::init_static(unsigned int sample_rate, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(sample_rate);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
#define fVslider0 (*fVslider0_)
#define fVslider1 (*fVslider1_)
#define fVslider2 (*fVslider2_)
#define fVslider3 (*fVslider3_)
	double fSlow0 = double(fVslider0);
	int iSlow1 = fSlow0 == 0.0;
	int iSlow2 = fSlow0 == 1.0;
	double fSlow3 = fConst1 * double(fVslider1);
	double fSlow4 = 4.748558434412966e-05 * (std::exp(5.0 * (1.0 - double(fVslider2))) + -1.0);
	double fSlow5 = double(fVslider3);
	double fSlow6 = fConst37 * fSlow5;
	double fSlow7 = 0.01 * fSlow5;
	double fSlow8 = 1.0 - fSlow7;
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		iVec0[0] = 1;
		fRec2[0] = fRec2[1] - fSlow3 * fRec0[1];
		fRec1[0] = fSlow3 * fRec2[0] + double(1 - iVec0[1]) + fRec1[1];
		fRec0[0] = fRec1[0];
		double fTemp0 = double(input0[i0]);
		double fTemp1 = std::fabs(fTemp0);
		fRec5[0] = std::max<double>(fTemp1, fConst3 * fRec5[1] + fConst4 * fTemp1);
		fRec4[0] = fConst5 * fRec5[0] + fConst2 * fRec4[1];
		fRec3[0] = 0.007000000000000006 * std::max<double>(0.1, std::min<double>(0.99, fRec4[0])) + 0.993 * fRec3[1];
		fRec6[0] = fSlow4 + 0.993 * fRec6[1];
		double fTemp2 = ((iSlow1) ? fRec6[0] : ((iSlow2) ? fRec3[0] : 1.0 - std::max<double>(0.01, std::min<double>(0.98, 0.5 * (fRec0[0] + 1.0)))));
		double fTemp3 = fConst12 + fTemp2 * (fConst10 + fConst8 * fTemp2) + 4.37440597864126e-11;
		fVec1[0] = fSlow6 * fTemp0;
		fRec8[0] = fConst39 * (fSlow7 * fTemp0 + fConst38 * fRec8[1]) - fVec1[1];
		fRec7[0] = fRec8[0] - (fRec7[1] * (fConst34 + fTemp2 * (fConst33 + fConst32 * fTemp2) + 1.7497623914565e-10) + fRec7[2] * (fConst7 * (fConst31 + fTemp2 * (fConst30 + fConst29 * fTemp2)) + 2.62464358718476e-10) + fRec7[3] * (fConst28 + fTemp2 * (fConst26 + fConst24 * fTemp2) + 1.7497623914565e-10) + fRec7[4] * (fConst22 + fTemp2 * (fConst21 + fConst20 * fTemp2) + 4.37440597864126e-11)) / fTemp3;
		output0[i0] = FAUSTFLOAT(fSlow8 * fTemp0 + (fConst7 * fRec7[2] * (fTemp2 * (fConst54 * fTemp2 + 8.50577002155424e-14 - fConst53) + 2.245310732952e-13 - fConst52) + fRec7[4] * (fConst51 + fTemp2 * (fConst50 + fConst49 * fTemp2)) + fRec7[0] * (fConst48 + fTemp2 * (fConst46 + fConst44 * fTemp2)) + fRec7[1] * (fConst42 + fTemp2 * (fConst41 + fConst40 * fTemp2)) + fRec7[3] * (fConst19 + fTemp2 * (fConst17 + fConst15 * fTemp2))) / fTemp3);
		iVec0[1] = iVec0[0];
		fRec2[1] = fRec2[0];
		fRec1[1] = fRec1[0];
		fRec0[1] = fRec0[0];
		fRec5[1] = fRec5[0];
		fRec4[1] = fRec4[0];
		fRec3[1] = fRec3[0];
		fRec6[1] = fRec6[0];
		fVec1[1] = fVec1[0];
		fRec8[1] = fRec8[0];
		for (int j0 = 4; j0 > 0; j0 = j0 - 1) {
			fRec7[j0] = fRec7[j0 - 1];
		}
	}
#undef fVslider0
#undef fVslider1
#undef fVslider2
#undef fVslider3
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	fVslider2_ = reg.registerFloatVar("wah.Wah","","SA","",&fVslider2, 0.0, 0.0, 1.0, 0.01, 0);
	fVslider1_ = reg.registerFloatVar("wah.freq",N_("Alien Freq"),"SA",N_("LFO in Beats per Minute"),&fVslider1, 24.0, 24.0, 3.6e+02, 1.0, 0);
	static const value_pair fVslider0_values[] = {{"manual"},{"auto"},{"alien"},{0}};
	fVslider0_ = reg.registerFloatVar("wah.mode","","SA","",&fVslider0, 0.0, 0.0, 2.0, 1.0, fVslider0_values);
	fVslider3_ = reg.registerFloatVar("wah.wet_dry",N_("dry/wet"),"SA","",&fVslider3, 1e+02, 0.0, 1e+02, 1.0, 0);
	return 0;
}

int Dsp::register_params_static(const ParamReg& reg)
{
	return static_cast<Dsp*>(reg.plugin)->register_par(reg);
}

PluginDef *plugin() {
	return new Dsp();
}

void Dsp::del_instance(PluginDef *p)
{
	delete static_cast<Dsp*>(p);
}

} // end namespace rolwah
