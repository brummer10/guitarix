// generated from file '../src/faust/colwah.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)


namespace colwah {

class Dsp: public PluginDef {
private:
	int fSampleRate;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	double fConst0;
	double fConst3;
	double fConst4;
	int iVec0[2];
	double fConst5;
	double fVec1[2];
	double fRec1[2];
	double fConst6;
	double fConst8;
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT	*fVslider1_;
	double fConst9;
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT	*fVslider2_;
	double fRec4[2];
	double fRec3[2];
	double fRec2[2];
	double fConst10;
	double fConst11;
	double fConst12;
	double fConst13;
	double fRec7[2];
	double fRec6[2];
	double fRec5[2];
	FAUSTFLOAT fVslider3;
	FAUSTFLOAT	*fVslider3_;
	double fRec8[2];
	double fConst15;
	double fConst17;
	double fConst18;
	double fConst19;
	double fConst20;
	double fConst21;
	double fConst22;
	double fConst23;
	double fConst25;
	double fConst27;
	double fConst29;
	double fConst30;
	double fConst31;
	double fConst32;
	double fRec0[5];
	double fConst34;
	double fConst36;
	double fConst38;
	double fConst40;
	double fConst42;
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
	for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) iVec0[l0] = 0;
	for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) fVec1[l1] = 0.0;
	for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) fRec1[l2] = 0.0;
	for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) fRec4[l3] = 0.0;
	for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) fRec3[l4] = 0.0;
	for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) fRec2[l5] = 0.0;
	for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) fRec7[l6] = 0.0;
	for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) fRec6[l7] = 0.0;
	for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) fRec5[l8] = 0.0;
	for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) fRec8[l9] = 0.0;
	for (int l10 = 0; (l10 < 5); l10 = (l10 + 1)) fRec0[l10] = 0.0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int sample_rate)
{
	fSampleRate = sample_rate;
	fConst0 = std::min<double>(192000.0, std::max<double>(1.0, double(fSampleRate)));
	double fConst1 = (491.77839701345533 / fConst0);
	double fConst2 = (fConst1 + 1.0);
	fConst3 = (1.0 / fConst2);
	fConst4 = (1.0 - fConst1);
	fConst5 = (0.01 / fConst2);
	fConst6 = mydsp_faustpower2_f(fConst0);
	double fConst7 = (2.6197539883514e-20 * fConst0);
	fConst8 = ((fConst6 * (-1.03086193732749e-17 - fConst7)) + 7.8953844813995607e-12);
	fConst9 = (0.10471975511965977 / fConst0);
	fConst10 = std::exp((0.0 - (100.0 / fConst0)));
	fConst11 = (1.0 - fConst10);
	fConst12 = std::exp((0.0 - (10.0 / fConst0)));
	fConst13 = (1.0 - fConst12);
	double fConst14 = (1.59074869637173e-18 * fConst0);
	fConst15 = ((fConst6 * (-5.41103154663699e-17 - fConst14)) + 1.4187933835940499e-12);
	double fConst16 = (2.7885341031362001e-19 * fConst0);
	fConst17 = ((fConst6 * (fConst16 + 1.16606130886395e-17)) + -4.7134411065708495e-13);
	fConst18 = ((3.9296309825271002e-20 * fConst6) + -2.5327061115886001e-13);
	fConst19 = ((2.3861230445575902e-18 * fConst6) + -3.8051075770230997e-14);
	fConst20 = (4.5936994895780199e-14 - (4.1828011547043002e-19 * fConst6));
	fConst21 = ((fConst6 * (1.03086193732749e-17 - fConst7)) + -7.8953844813995607e-12);
	fConst22 = ((fConst6 * (5.41103154663699e-17 - fConst14)) + -1.4187933835940499e-12);
	fConst23 = ((fConst6 * (fConst16 + -1.16606130886395e-17)) + 4.7134411065708495e-13);
	double fConst24 = (6.5493849708784901e-21 * fConst0);
	fConst25 = ((fConst0 * ((fConst0 * (fConst24 + -5.1543096866374301e-18)) + 1.2663530557943001e-13)) + -3.9476922406997804e-12);
	double fConst26 = (3.9768717409293202e-19 * fConst0);
	fConst27 = ((fConst0 * ((fConst0 * (fConst26 + -2.7055157733184901e-17)) + 1.9025537885115499e-14)) + -7.0939669179702304e-13);
	double fConst28 = (6.9713352578405003e-20 * fConst0);
	fConst29 = ((fConst0 * ((fConst0 * (5.8303065443197298e-18 - fConst28)) + -2.29684974478901e-14)) + 2.3567205532854298e-13);
	fConst30 = ((fConst0 * ((fConst0 * (fConst24 + 5.1543096866374301e-18)) + 1.2663530557943001e-13)) + 3.9476922406997804e-12);
	fConst31 = ((fConst0 * ((fConst0 * (fConst26 + 2.7055157733184901e-17)) + 1.9025537885115499e-14)) + 7.0939669179702304e-13);
	fConst32 = ((fConst0 * ((fConst0 * (-5.8303065443197298e-18 - fConst28)) + -2.29684974478901e-14)) + -2.3567205532854298e-13);
	double fConst33 = (2.6692667513262201e-21 * fConst0);
	fConst34 = ((fConst0 * ((fConst0 * (-8.4353411530683398e-17 - fConst33)) + -1.31405791553819e-13)) + -6.8163310136895803e-13);
	double fConst35 = (8.2257982773123304e-22 * fConst0);
	fConst36 = ((fConst0 * ((fConst0 * (-1.8944566310570602e-17 - fConst35)) + -2.9231175110574099e-14)) + -6.2551948406914103e-13);
	double fConst37 = (8.3124905205088099e-22 * fConst0);
	fConst38 = (fConst0 * ((fConst0 * (fConst37 + 1.9125057672039999e-17)) + 2.9122542229414998e-14));
	double fConst39 = (1.06770670053049e-20 * fConst0);
	fConst40 = ((fConst6 * (fConst39 + 1.6870682306136699e-16)) + -1.3632662027379201e-12);
	double fConst41 = (3.2903193109249299e-21 * fConst0);
	fConst42 = ((fConst6 * (fConst41 + 3.7889132621141302e-17)) + -1.25103896813828e-12);
	double fConst43 = (3.3249962082035198e-21 * fConst0);
	fConst44 = (fConst6 * (-3.8250115344079997e-17 - fConst43));
	fConst45 = (2.6281158310763801e-13 - (1.6015600507957301e-20 * fConst6));
	fConst46 = (5.8462350221148298e-14 - (4.9354789663874001e-21 * fConst6));
	fConst47 = ((4.9874943123052901e-21 * fConst6) + -5.8245084458829996e-14);
	fConst48 = ((fConst6 * (fConst39 + -1.6870682306136699e-16)) + 1.3632662027379201e-12);
	fConst49 = ((fConst6 * (fConst41 + -3.7889132621141302e-17)) + 1.25103896813828e-12);
	fConst50 = (fConst6 * (3.8250115344079997e-17 - fConst43));
	fConst51 = ((fConst0 * ((fConst0 * (8.4353411530683398e-17 - fConst33)) + -1.31405791553819e-13)) + 6.8163310136895803e-13);
	fConst52 = ((fConst0 * ((fConst0 * (1.8944566310570602e-17 - fConst35)) + -2.9231175110574099e-14)) + 6.2551948406914103e-13);
	fConst53 = (fConst0 * ((fConst0 * (fConst37 + -1.9125057672039999e-17)) + 2.9122542229414998e-14));
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
	double fSlow1 = (0.01 * fSlow0);
	double fSlow2 = (1.0 - fSlow1);
	double fSlow3 = (fConst5 * fSlow0);
	int iSlow4 = int(double(fVslider1));
	int iSlow5 = (iSlow4 == 0);
	int iSlow6 = (iSlow4 == 1);
	double fSlow7 = (fConst9 * double(fVslider2));
	double fSlow8 = (4.748558434412966e-05 * (std::exp((5.0 * (1.0 - std::max<double>(0.01, double(fVslider3))))) + -1.0));
	for (int i0 = 0; (i0 < count); i0 = (i0 + 1)) {
		double fTemp0 = double(input0[i0]);
		iVec0[0] = 1;
		fVec1[0] = (fSlow3 * fTemp0);
		fRec1[0] = ((fConst3 * ((fSlow1 * fTemp0) + (fConst4 * fRec1[1]))) - fVec1[1]);
		fRec4[0] = (fRec4[1] + (fSlow7 * (0.0 - fRec2[1])));
		fRec3[0] = ((fSlow7 * fRec4[0]) + (double((1 - iVec0[1])) + fRec3[1]));
		fRec2[0] = fRec3[0];
		double fTemp1 = std::fabs(fTemp0);
		fRec7[0] = std::max<double>(fTemp1, ((fConst12 * fRec7[1]) + (fConst13 * fTemp1)));
		fRec6[0] = ((fConst10 * fRec6[1]) + (fConst11 * fRec7[0]));
		fRec5[0] = ((0.99299999999999999 * fRec5[1]) + (0.0070000000000000062 * std::max<double>(0.02, std::min<double>(1.0, fRec6[0]))));
		double fThen0 = (1.0 - std::max<double>(0.02, std::min<double>(0.97999999999999998, (0.5 * (fRec2[0] + 1.0)))));
		fRec8[0] = (fSlow8 + (0.99299999999999999 * fRec8[1]));
		double fThen1 = (iSlow6 ? fRec5[0] : fThen0);
		double fTemp2 = (iSlow5 ? fRec8[0] : fThen1);
		double fTemp3 = ((fConst0 * (fConst30 + (fTemp2 * (fConst31 + (fConst32 * fTemp2))))) + 1.63948058636323e-11);
		fRec0[0] = (fRec1[0] - (((((fRec0[1] * ((fConst0 * (fConst8 + (fTemp2 * (fConst15 + (fConst17 * fTemp2))))) + 6.5579223454529095e-11)) + (fRec0[2] * ((fConst6 * (fConst18 + (fTemp2 * (fConst19 + (fConst20 * fTemp2))))) + 9.8368835181793604e-11))) + (fRec0[3] * ((fConst0 * (fConst21 + (fTemp2 * (fConst22 + (fConst23 * fTemp2))))) + 6.5579223454529095e-11))) + (fRec0[4] * ((fConst0 * (fConst25 + (fTemp2 * (fConst27 + (fConst29 * fTemp2))))) + 1.63948058636323e-11))) / fTemp3));
		output0[i0] = FAUSTFLOAT(((fSlow2 * fTemp0) + (fConst0 * ((((((fRec0[0] * (fConst34 + (fTemp2 * (fConst36 + (fConst38 * fTemp2))))) + (fRec0[1] * (fConst40 + (fTemp2 * (fConst42 + (fConst44 * fTemp2)))))) + (fConst0 * (fRec0[2] * (fConst45 + (fTemp2 * (fConst46 + (fConst47 * fTemp2))))))) + (fRec0[3] * (fConst48 + (fTemp2 * (fConst49 + (fConst50 * fTemp2)))))) + (fRec0[4] * (fConst51 + (fTemp2 * (fConst52 + (fConst53 * fTemp2)))))) / fTemp3))));
		iVec0[1] = iVec0[0];
		fVec1[1] = fVec1[0];
		fRec1[1] = fRec1[0];
		fRec4[1] = fRec4[0];
		fRec3[1] = fRec3[0];
		fRec2[1] = fRec2[0];
		fRec7[1] = fRec7[0];
		fRec6[1] = fRec6[0];
		fRec5[1] = fRec5[0];
		fRec8[1] = fRec8[0];
		for (int j0 = 4; (j0 > 0); j0 = (j0 - 1)) {
			fRec0[j0] = fRec0[(j0 - 1)];
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
	fVslider3_ = reg.registerFloatVar("wah.Wah","","SA","",&fVslider3, 0.0, 0.0, 1.0, 0.01, 0);
	fVslider2_ = reg.registerFloatVar("wah.freq",N_("Alien Freq"),"SA",N_("LFO in Beats per Minute"),&fVslider2, 24.0, 24.0, 360.0, 1.0, 0);
	static const value_pair fVslider1_values[] = {{"manual"},{"auto"},{"alien"},{0}};
	fVslider1_ = reg.registerFloatVar("wah.mode","","SA","",&fVslider1, 0.0, 0.0, 2.0, 1.0, fVslider1_values);
	fVslider0_ = reg.registerFloatVar("wah.wet_dry",N_("dry/wet"),"SA","",&fVslider0, 100.0, 0.0, 100.0, 1.0, 0);
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
