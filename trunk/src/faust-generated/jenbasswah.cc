// generated from file '../src/faust/jenbasswah.dsp' by dsp2cc:
// Code generated with Faust 2.15.11 (https://faust.grame.fr)


namespace jenbasswah {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT	*fVslider0_;
	double fConst0;
	double fConst1;
	double fConst2;
	double fConst3;
	double fConst4;
	int iVec0[2];
	double fConst5;
	double fVec1[2];
	double fRec1[2];
	double fConst6;
	double fConst7;
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
	double fRec0[5];
	double fConst33;
	double fConst34;
	double fConst35;
	double fConst36;
	double fConst37;
	double fConst38;
	double fConst39;
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

	void clear_state_f();
	void init(unsigned int samplingFreq);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0);
	int register_par(const ParamReg& reg);

	static void clear_state_f_static(PluginDef*);
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
	id = "jenbasswah";
	name = N_("Jen Bass Wah");
	groups = 0;
	description = N_("Jen BassWah"); // description (tooltip)
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

inline void Dsp::init(unsigned int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = std::min<double>(192000.0, std::max<double>(1.0, double(fSamplingFreq)));
	fConst1 = (718.2824771643642 / fConst0);
	fConst2 = (fConst1 + 1.0);
	fConst3 = (1.0 / fConst2);
	fConst4 = (1.0 - fConst1);
	fConst5 = (0.01 / fConst2);
	fConst6 = (4.7621855669811301e-20 * fConst0);
	fConst7 = mydsp_faustpower2_f(fConst0);
	fConst8 = (((-1.2498034136331e-17 - fConst6) * fConst7) + 3.24361444911983e-12);
	fConst9 = (0.10471975511965977 / fConst0);
	fConst10 = std::exp((0.0 - (100.0 / fConst0)));
	fConst11 = (1.0 - fConst10);
	fConst12 = std::exp((0.0 - (10.0 / fConst0)));
	fConst13 = (1.0 - fConst12);
	fConst14 = (1.5494015443595901e-18 * fConst0);
	fConst15 = (((-4.6157566175488903e-17 - fConst14) * fConst7) + 8.1331268524130996e-13);
	fConst16 = (2.8105136755319898e-19 * fConst0);
	fConst17 = ((fConst16 + 1.6916459333518401e-17) * fConst7);
	fConst18 = ((7.1432783504717006e-20 * fConst7) + -1.7113782505556501e-13);
	fConst19 = ((2.3241023165393899e-18 * fConst7) + -3.1449960940446399e-14);
	fConst20 = (3.5785758150617602e-14 - (4.2157705132979898e-19 * fConst7));
	fConst21 = (((1.2498034136331e-17 - fConst6) * fConst7) + -3.24361444911983e-12);
	fConst22 = (((4.6157566175488903e-17 - fConst14) * fConst7) + -8.1331268524130996e-13);
	fConst23 = ((fConst16 + -1.6916459333518401e-17) * fConst7);
	fConst24 = (1.19054639174528e-20 * fConst0);
	fConst25 = (((((fConst24 + -6.2490170681655099e-18) * fConst0) + 8.5568912527782405e-14) * fConst0) + -1.62180722455991e-12);
	fConst26 = (3.87350386089898e-19 * fConst0);
	fConst27 = (((((fConst26 + -2.3078783087744399e-17) * fConst0) + 1.57249804702232e-14) * fConst0) + -4.0665634262065498e-13);
	fConst28 = (7.0262841888299805e-20 * fConst0);
	fConst29 = ((((8.4582296667591807e-18 - fConst28) * fConst0) + -1.7892879075308801e-14) * fConst0);
	fConst30 = (((((fConst24 + 6.2490170681655099e-18) * fConst0) + 8.5568912527782405e-14) * fConst0) + 1.62180722455991e-12);
	fConst31 = (((((fConst26 + 2.3078783087744399e-17) * fConst0) + 1.57249804702232e-14) * fConst0) + 4.0665634262065498e-13);
	fConst32 = ((((-8.4582296667591807e-18 - fConst28) * fConst0) + -1.7892879075308801e-14) * fConst0);
	fConst33 = (7.4790171060125594e-21 * fConst0);
	fConst34 = (((((-3.7062029784419503e-17 - fConst33) * fConst0) + -5.2201218632342101e-14) * fConst0) + -3.0917776550512901e-15);
	fConst35 = (4.2676505166436901e-21 * fConst0);
	fConst36 = (((((-1.30609446727126e-17 - fConst35) * fConst0) + -1.3782974775989e-14) * fConst0) + -2.52409371323892e-13);
	fConst37 = (4.2811577536333903e-21 * fConst0);
	fConst38 = ((((fConst37 + 1.30268272702044e-17) * fConst0) + 1.36038216822257e-14) * fConst0);
	fConst39 = (2.9916068424050201e-20 * fConst0);
	fConst40 = (((fConst39 + 7.4124059568839006e-17) * fConst7) + -6.1835553101025897e-15);
	fConst41 = (1.70706020665747e-20 * fConst0);
	fConst42 = (((fConst41 + 2.6121889345425199e-17) * fConst7) + -5.04818742647784e-13);
	fConst43 = (1.7124631014533501e-20 * fConst0);
	fConst44 = ((-2.6053654540408701e-17 - fConst43) * fConst7);
	fConst45 = (1.04402437264684e-13 - (4.4874102636075398e-20 * fConst7));
	fConst46 = (2.7565949551978099e-14 - (2.56059030998621e-20 * fConst7));
	fConst47 = ((2.56869465218003e-20 * fConst7) + -2.72076433644514e-14);
	fConst48 = (((fConst39 + -7.4124059568839006e-17) * fConst7) + 6.1835553101025897e-15);
	fConst49 = (((fConst41 + -2.6121889345425199e-17) * fConst7) + 5.04818742647784e-13);
	fConst50 = ((2.6053654540408701e-17 - fConst43) * fConst7);
	fConst51 = (((((3.7062029784419503e-17 - fConst33) * fConst0) + -5.2201218632342101e-14) * fConst0) + 3.0917776550512901e-15);
	fConst52 = (((((1.30609446727126e-17 - fConst35) * fConst0) + -1.3782974775989e-14) * fConst0) + 2.52409371323892e-13);
	fConst53 = ((((fConst37 + -1.30268272702044e-17) * fConst0) + 1.36038216822257e-14) * fConst0);
	fVslider0 = FAUSTFLOAT(100.0);
	fVslider1 = FAUSTFLOAT(0.0);
	fVslider2 = FAUSTFLOAT(24.0);
	fVslider3 = FAUSTFLOAT(0.0);
	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
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
	double fSlow8 = (4.748558434412966e-05 * (std::exp((5.0 * (1.0 - double(fVslider3)))) + -1.0));
	for (int i = 0; (i < count); i = (i + 1)) {
		double fTemp0 = double(input0[i]);
		iVec0[0] = 1;
		fVec1[0] = (fSlow3 * fTemp0);
		fRec1[0] = ((fConst3 * ((fSlow1 * fTemp0) + (fConst4 * fRec1[1]))) - fVec1[1]);
		fRec4[0] = (fRec4[1] + (fSlow7 * (0.0 - fRec2[1])));
		fRec3[0] = ((fSlow7 * fRec4[0]) + (double((1 - iVec0[1])) + fRec3[1]));
		fRec2[0] = fRec3[0];
		double fTemp1 = std::fabs(fTemp0);
		fRec7[0] = std::max<double>(fTemp1, ((fConst12 * fRec7[1]) + (fConst13 * fTemp1)));
		fRec6[0] = ((fConst10 * fRec6[1]) + (fConst11 * fRec7[0]));
		fRec5[0] = ((0.99299999999999999 * fRec5[1]) + (0.0070000000000000062 * std::max<double>(0.10000000000000001, std::min<double>(0.98999999999999999, fRec6[0]))));
		fRec8[0] = (fSlow8 + (0.99299999999999999 * fRec8[1]));
		double fTemp2 = (iSlow5?fRec8[0]:(iSlow6?fRec5[0]:(1.0 - std::max<double>(0.01, std::min<double>(0.97999999999999998, (0.5 * (fRec2[0] + 1.0)))))));
		double fTemp3 = ((fConst0 * (fConst30 + (fTemp2 * (fConst31 + (fConst32 * fTemp2))))) + 9.2421896050148795e-14);
		fRec0[0] = (fRec1[0] - (((((fRec0[1] * ((fConst0 * (fConst8 + (fTemp2 * (fConst15 + (fConst17 * fTemp2))))) + 3.6968758420059498e-13)) + (fRec0[2] * ((fConst7 * (fConst18 + (fTemp2 * (fConst19 + (fConst20 * fTemp2))))) + 5.5453137630089302e-13))) + (fRec0[3] * ((fConst0 * (fConst21 + (fTemp2 * (fConst22 + (fConst23 * fTemp2))))) + 3.6968758420059498e-13))) + (fRec0[4] * ((fConst0 * (fConst25 + (fTemp2 * (fConst27 + (fConst29 * fTemp2))))) + 9.2421896050148795e-14))) / fTemp3));
		output0[i] = FAUSTFLOAT(((fSlow2 * fTemp0) + (fConst0 * ((((((fRec0[0] * (fConst34 + (fTemp2 * (fConst36 + (fConst38 * fTemp2))))) + (fRec0[1] * (fConst40 + (fTemp2 * (fConst42 + (fConst44 * fTemp2)))))) + (fConst0 * (fRec0[2] * (fConst45 + (fTemp2 * (fConst46 + (fConst47 * fTemp2))))))) + (fRec0[3] * (fConst48 + (fTemp2 * (fConst49 + (fConst50 * fTemp2)))))) + (fRec0[4] * (fConst51 + (fTemp2 * (fConst52 + (fConst53 * fTemp2)))))) / fTemp3))));
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
	fVslider3_ = reg.registerVar("wah.Wah","","SA","",&fVslider3, 0.0, 0.0, 1.0, 0.01);
	fVslider2_ = reg.registerVar("wah.freq",N_("Alien Freq"),"SA",N_("LFO in Beats per Minute"),&fVslider2, 24.0, 24.0, 360.0, 1.0);
	static const value_pair fVslider1_values[] = {{"manual"},{"auto"},{"alien"},{0}};
	fVslider1_ = reg.registerSharedEnumVar("wah.mode","","SA","",fVslider1_values,&fVslider1, 0.0, 0.0, 2.0, 1.0);
	fVslider0_ = reg.registerVar("wah.wet_dry",N_("dry/wet"),"SA","",&fVslider0, 100.0, 0.0, 100.0, 1.0);
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

} // end namespace jenbasswah
