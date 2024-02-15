// generated from file '../src/faust/colwah.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)


namespace colwah {

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
	double fConst7;
	double fConst9;
	double fConst11;
	double fConst14;
	double fConst16;
	double fConst17;
	double fConst19;
	double fConst20;
	double fConst21;
	double fConst22;
	double fConst23;
	double fConst24;
	double fConst26;
	double fConst28;
	double fConst30;
	double fConst31;
	double fConst32;
	double fConst33;
	double fConst34;
	double fConst35;
	double fConst36;
	FAUSTFLOAT fVslider3;
	FAUSTFLOAT	*fVslider3_;
	double fConst39;
	double fVec1[2];
	double fConst40;
	double fConst41;
	double fRec8[2];
	double fRec7[5];
	double fConst42;
	double fConst43;
	double fConst44;
	double fConst46;
	double fConst48;
	double fConst50;
	double fConst51;
	double fConst52;
	double fConst53;
	double fConst54;
	double fConst55;
	double fConst56;

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
	id = "colwah";
	name = N_("ColorSound Wah");
	groups = 0;
	description = N_("ColorSound Wah"); // description (tooltip)
	category = N_("Guitar Effects");       // category
	shortname = N_("ColorSound Wah");     // shortname
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
	double fConst6 = 6.9713352578405e-20 * fConst0;
	fConst7 = fConst0 * (fConst0 * (-5.83030654431973e-18 - fConst6) + -2.29684974478901e-14) + -2.35672055328543e-13;
	double fConst8 = 3.97687174092932e-19 * fConst0;
	fConst9 = fConst0 * (fConst0 * (fConst8 + 2.70551577331849e-17) + 1.90255378851155e-14);
	double fConst10 = 6.54938497087849e-21 * fConst0;
	fConst11 = fConst0 * (fConst0 * (fConst10 + 5.15430968663743e-18) + 1.2663530557943e-13);
	double fConst12 = 3.32499620820352e-21 * fConst0;
	double fConst13 = mydsp_faustpower3_f(fConst0);
	fConst14 = fConst13 * (3.825011534408e-17 - fConst12);
	double fConst15 = 3.29031931092493e-21 * fConst0;
	fConst16 = mydsp_faustpower2_f(fConst0);
	fConst17 = fConst0 * (fConst16 * (fConst15 + -3.78891326211413e-17) + 1.25103896813828e-12);
	double fConst18 = 1.06770670053049e-20 * fConst0;
	fConst19 = fConst0 * (fConst16 * (fConst18 + -1.68706823061367e-16) + 1.36326620273792e-12);
	fConst20 = fConst9 + 7.09396691797023e-13;
	fConst21 = fConst11 + 3.94769224069978e-12;
	fConst22 = fConst0 * (fConst0 * (5.83030654431973e-18 - fConst6) + -2.29684974478901e-14) + 2.35672055328543e-13;
	fConst23 = fConst0 * (fConst0 * (fConst8 + -2.70551577331849e-17) + 1.90255378851155e-14) + -7.09396691797023e-13;
	fConst24 = fConst0 * (fConst0 * (fConst10 + -5.15430968663743e-18) + 1.2663530557943e-13) + -3.94769224069978e-12;
	double fConst25 = 2.7885341031362e-19 * fConst0;
	fConst26 = fConst16 * (fConst25 + -1.16606130886395e-17) + 4.71344110657085e-13;
	double fConst27 = 1.59074869637173e-18 * fConst0;
	fConst28 = fConst16 * (5.41103154663699e-17 - fConst27) + -1.41879338359405e-12;
	double fConst29 = 2.6197539883514e-20 * fConst0;
	fConst30 = fConst16 * (1.03086193732749e-17 - fConst29) + -7.89538448139956e-12;
	fConst31 = 4.59369948957802e-14 - 4.1828011547043e-19 * fConst16;
	fConst32 = 2.38612304455759e-18 * fConst16 + -3.8051075770231e-14;
	fConst33 = 3.9296309825271e-20 * fConst16 + -2.5327061115886e-13;
	fConst34 = fConst16 * (fConst25 + 1.16606130886395e-17) + -4.71344110657085e-13;
	fConst35 = fConst16 * (-5.41103154663699e-17 - fConst27) + 1.41879338359405e-12;
	fConst36 = fConst16 * (-1.03086193732749e-17 - fConst29) + 7.89538448139956e-12;
	double fConst37 = 491.77839701345533 / fConst0;
	double fConst38 = fConst37 + 1.0;
	fConst39 = 0.01 / fConst38;
	fConst40 = 1.0 - fConst37;
	fConst41 = 1.0 / fConst38;
	fConst42 = fConst13 * (-3.825011534408e-17 - fConst12);
	fConst43 = fConst0 * (fConst16 * (fConst15 + 3.78891326211413e-17) + -1.25103896813828e-12);
	fConst44 = fConst0 * (fConst16 * (fConst18 + 1.68706823061367e-16) + -1.36326620273792e-12);
	double fConst45 = 8.31249052050881e-22 * fConst0;
	fConst46 = fConst16 * (fConst0 * (fConst45 + 1.912505767204e-17) + 2.9122542229415e-14);
	double fConst47 = 8.22579827731233e-22 * fConst0;
	fConst48 = fConst0 * (fConst0 * (fConst0 * (-1.89445663105706e-17 - fConst47) + -2.92311751105741e-14) + -6.25519484069141e-13);
	double fConst49 = 2.66926675132622e-21 * fConst0;
	fConst50 = fConst0 * (fConst0 * (fConst0 * (-8.43534115306834e-17 - fConst49) + -1.31405791553819e-13) + -6.81633101368958e-13);
	fConst51 = fConst16 * (fConst0 * (fConst45 + -1.912505767204e-17) + 2.9122542229415e-14);
	fConst52 = fConst0 * (fConst0 * (fConst0 * (1.89445663105706e-17 - fConst47) + -2.92311751105741e-14) + 6.25519484069141e-13);
	fConst53 = fConst0 * (fConst0 * (fConst0 * (8.43534115306834e-17 - fConst49) + -1.31405791553819e-13) + 6.81633101368958e-13);
	fConst54 = 1.60156005079573e-20 * fConst16;
	fConst55 = 4.9354789663874e-21 * fConst16;
	fConst56 = 4.98749431230529e-21 * fConst16 + -5.824508445883e-14;
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
	double fSlow4 = 4.748558434412966e-05 * (std::exp(5.0 * (1.0 - std::max<double>(0.01, double(fVslider2)))) + -1.0);
	double fSlow5 = double(fVslider3);
	double fSlow6 = fConst39 * fSlow5;
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
		fRec3[0] = 0.007000000000000006 * std::max<double>(0.02, std::min<double>(1.0, fRec4[0])) + 0.993 * fRec3[1];
		fRec6[0] = fSlow4 + 0.993 * fRec6[1];
		double fTemp2 = ((iSlow1) ? fRec6[0] : ((iSlow2) ? fRec3[0] : 1.0 - std::max<double>(0.02, std::min<double>(0.98, 0.5 * (fRec0[0] + 1.0)))));
		double fTemp3 = fConst7 * fTemp2;
		fVec1[0] = fSlow6 * fTemp0;
		fRec8[0] = fConst41 * (fSlow7 * fTemp0 + fConst40 * fRec8[1]) - fVec1[1];
		fRec7[0] = fRec8[0] - (fRec7[1] * (fConst0 * (fConst36 + fTemp2 * (fConst35 + fConst34 * fTemp2)) + 6.55792234545291e-11) + fRec7[2] * (fConst16 * (fConst33 + fTemp2 * (fConst32 + fConst31 * fTemp2)) + 9.83688351817936e-11) + fRec7[3] * (fConst0 * (fConst30 + fTemp2 * (fConst28 + fConst26 * fTemp2)) + 6.55792234545291e-11) + fRec7[4] * (fConst0 * (fConst24 + fTemp2 * (fConst23 + fConst22 * fTemp2)) + 1.63948058636323e-11)) / (fConst0 * (fConst21 + fTemp2 * (fConst20 + fTemp3)) + 1.63948058636323e-11);
		output0[i0] = FAUSTFLOAT(fSlow8 * fTemp0 + (fConst16 * fRec7[2] * (fTemp2 * (fConst56 * fTemp2 + 5.84623502211483e-14 - fConst55) + 2.62811583107638e-13 - fConst54) + fRec7[4] * (fConst53 + fTemp2 * (fConst52 + fConst51 * fTemp2)) + fRec7[0] * (fConst50 + fTemp2 * (fConst48 + fConst46 * fTemp2)) + fRec7[1] * (fConst44 + fTemp2 * (fConst43 + fConst42 * fTemp2)) + fRec7[3] * (fConst19 + fTemp2 * (fConst17 + fConst14 * fTemp2))) / (fConst0 * (fConst11 + fTemp2 * (fConst9 + fTemp3 + 7.09396691797023e-13) + 3.94769224069978e-12) + 1.63948058636323e-11));
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

} // end namespace colwah
