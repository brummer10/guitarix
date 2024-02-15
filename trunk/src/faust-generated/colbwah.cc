// generated from file '../src/faust/colbwah.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)


namespace colbwah {

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
	double fRec4[2];
	double fConst5;
	double fRec3[2];
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT	*fVslider2_;
	double fRec5[2];
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
	double fRec7[2];
	double fRec6[5];
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
	id = "colbwah";
	name = N_("ColorSound Bass Wah");
	groups = 0;
	description = N_("ColorSound Bass Wah"); // description (tooltip)
	category = N_("Guitar Effects");       // category
	shortname = N_("ColorSound Bass Wah");     // shortname
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
	for (int l4 = 0; l4 < 2; l4 = l4 + 1) fRec4[l4] = 0.0;
	for (int l5 = 0; l5 < 2; l5 = l5 + 1) fRec3[l5] = 0.0;
	for (int l6 = 0; l6 < 2; l6 = l6 + 1) fRec5[l6] = 0.0;
	for (int l7 = 0; l7 < 2; l7 = l7 + 1) fVec1[l7] = 0.0;
	for (int l8 = 0; l8 < 2; l8 = l8 + 1) fRec7[l8] = 0.0;
	for (int l9 = 0; l9 < 5; l9 = l9 + 1) fRec6[l9] = 0.0;
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
	double fConst6 = 6.97503428259418e-20 * fConst0;
	fConst7 = fConst0 * (fConst0 * (-5.39620091780675e-18 - fConst6) + -3.42307552972106e-15) + -3.4676044717882e-14;
	double fConst8 = 3.97898188862218e-19 * fConst0;
	fConst9 = fConst0 * (fConst0 * (fConst8 + 2.67097118338883e-17) + 2.93048706029115e-15);
	double fConst10 = 6.5528601067591e-21 * fConst0;
	fConst11 = fConst0 * (fConst0 * (fConst10 + 2.74563396261683e-18) + 1.8780340503575e-14);
	double fConst12 = 3.32676046755058e-21 * fConst0;
	double fConst13 = mydsp_faustpower3_f(fConst0);
	fConst14 = fConst13 * (6.40759622390608e-18 - fConst12);
	double fConst15 = 3.29206517053968e-21 * fConst0;
	fConst16 = mydsp_faustpower2_f(fConst0);
	fConst17 = fConst0 * (fConst16 * (fConst15 + -6.36826857609764e-18) + 1.84073937583106e-13);
	double fConst18 = 1.06827323096148e-20 * fConst0;
	fConst19 = fConst0 * (fConst16 * (fConst18 + -2.55156458656466e-17) + 2.00586699777507e-13);
	fConst20 = fConst9 + 1.04378397231604e-13;
	fConst21 = fConst11 + 5.83881532956283e-13;
	fConst22 = fConst0 * (fConst0 * (5.39620091780675e-18 - fConst6) + -3.42307552972106e-15) + 3.4676044717882e-14;
	fConst23 = fConst0 * (fConst0 * (fConst8 + -2.67097118338883e-17) + 2.93048706029115e-15) + -1.04378397231604e-13;
	fConst24 = fConst0 * (fConst0 * (fConst10 + -2.74563396261683e-18) + 1.8780340503575e-14) + -5.83881532956283e-13;
	double fConst25 = 2.79001371303767e-19 * fConst0;
	fConst26 = fConst16 * (fConst25 + -1.07924018356135e-17) + 6.9352089435764e-14;
	double fConst27 = 1.59159275544887e-18 * fConst0;
	fConst28 = fConst16 * (5.34194236677766e-17 - fConst27) + -2.08756794463207e-13;
	double fConst29 = 2.62114404270364e-20 * fConst0;
	fConst30 = fConst16 * (5.49126792523366e-18 - fConst29) + -1.16776306591257e-12;
	fConst31 = 6.84615105944212e-15 - 4.18502056955651e-19 * fConst16;
	fConst32 = 2.38738913317331e-18 * fConst16 + -5.8609741205823e-15;
	fConst33 = 3.93171606405546e-20 * fConst16 + -3.75606810071501e-14;
	fConst34 = fConst16 * (fConst25 + 1.07924018356135e-17) + -6.9352089435764e-14;
	fConst35 = fConst16 * (-5.34194236677766e-17 - fConst27) + 2.08756794463207e-13;
	fConst36 = fConst16 * (-5.49126792523366e-18 - fConst29) + 1.16776306591257e-12;
	double fConst37 = 493.6899529387045 / fConst0;
	double fConst38 = fConst37 + 1.0;
	fConst39 = 0.01 / fConst38;
	fConst40 = 1.0 - fConst37;
	fConst41 = 1.0 / fConst38;
	fConst42 = fConst13 * (-6.40759622390608e-18 - fConst12);
	fConst43 = fConst0 * (fConst16 * (fConst15 + 6.36826857609764e-18) + -1.84073937583106e-13);
	fConst44 = fConst0 * (fConst16 * (fConst18 + 2.55156458656466e-17) + -2.00586699777507e-13);
	double fConst45 = 8.31690116887645e-22 * fConst0;
	fConst46 = fConst16 * (fConst0 * (fConst45 + 3.20379811195304e-18) + 4.28499923433696e-15);
	double fConst47 = 8.23016292634919e-22 * fConst0;
	fConst48 = fConst0 * (fConst0 * (fConst0 * (-3.18413428804882e-18 - fConst47) + -4.30254138569803e-15) + -9.2036968791553e-14);
	double fConst49 = 2.6706830774037e-21 * fConst0;
	fConst50 = fConst0 * (fConst0 * (fConst0 * (-1.27578229328233e-17 - fConst49) + -1.93436893661132e-14) + -1.00293349888753e-13);
	fConst51 = fConst16 * (fConst0 * (fConst45 + -3.20379811195304e-18) + 4.28499923433696e-15);
	fConst52 = fConst0 * (fConst0 * (fConst0 * (3.18413428804882e-18 - fConst47) + -4.30254138569803e-15) + 9.2036968791553e-14);
	fConst53 = fConst0 * (fConst0 * (fConst0 * (1.27578229328233e-17 - fConst49) + -1.93436893661132e-14) + 1.00293349888753e-13);
	fConst54 = 1.60240984644222e-20 * fConst16;
	fConst55 = 4.93809775580952e-21 * fConst16;
	fConst56 = 4.99014070132587e-21 * fConst16 + -8.56999846867392e-15;
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
		fRec4[0] = std::max<double>(fTemp1, fConst3 * fRec4[1] + fConst4 * fTemp1);
		fRec3[0] = fConst5 * fRec4[0] + fConst2 * fRec3[1];
		fRec5[0] = fSlow4 + 0.993 * fRec5[1];
		double fTemp2 = ((iSlow1) ? fRec5[0] : ((iSlow2) ? std::max<double>(0.02, std::min<double>(1.0, fRec3[0])) : 1.0 - std::max<double>(0.02, std::min<double>(0.98, 0.5 * (fRec0[0] + 1.0)))));
		double fTemp3 = fConst7 * fTemp2;
		fVec1[0] = fSlow6 * fTemp0;
		fRec7[0] = fConst41 * (fSlow7 * fTemp0 + fConst40 * fRec7[1]) - fVec1[1];
		fRec6[0] = fRec7[0] - (fRec6[1] * (fConst0 * (fConst36 + fTemp2 * (fConst35 + fConst34 * fTemp2)) + 9.64912060491465e-12) + fRec6[2] * (fConst16 * (fConst33 + fTemp2 * (fConst32 + fConst31 * fTemp2)) + 1.4473680907372e-11) + fRec6[3] * (fConst0 * (fConst30 + fTemp2 * (fConst28 + fConst26 * fTemp2)) + 9.64912060491465e-12) + fRec6[4] * (fConst0 * (fConst24 + fTemp2 * (fConst23 + fConst22 * fTemp2)) + 2.41228015122866e-12)) / (fConst0 * (fConst21 + fTemp2 * (fConst20 + fTemp3)) + 2.41228015122866e-12);
		output0[i0] = FAUSTFLOAT(fSlow8 * fTemp0 + (fConst16 * fRec6[2] * (fTemp2 * (fConst56 * fTemp2 + 8.60508277139606e-15 - fConst55) + 3.86873787322263e-14 - fConst54) + fRec6[4] * (fConst53 + fTemp2 * (fConst52 + fConst51 * fTemp2)) + fRec6[0] * (fConst50 + fTemp2 * (fConst48 + fConst46 * fTemp2)) + fRec6[1] * (fConst44 + fTemp2 * (fConst43 + fConst42 * fTemp2)) + fRec6[3] * (fConst19 + fTemp2 * (fConst17 + fConst14 * fTemp2))) / (fConst0 * (fConst11 + fTemp2 * (fConst9 + fTemp3 + 1.04378397231604e-13) + 5.83881532956283e-13) + 2.41228015122866e-12));
		iVec0[1] = iVec0[0];
		fRec2[1] = fRec2[0];
		fRec1[1] = fRec1[0];
		fRec0[1] = fRec0[0];
		fRec4[1] = fRec4[0];
		fRec3[1] = fRec3[0];
		fRec5[1] = fRec5[0];
		fVec1[1] = fVec1[0];
		fRec7[1] = fRec7[0];
		for (int j0 = 4; j0 > 0; j0 = j0 - 1) {
			fRec6[j0] = fRec6[j0 - 1];
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

} // end namespace colbwah
