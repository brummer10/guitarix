// generated from file '../src/faust/colbwah.dsp' by dsp2cc:
// Code generated with Faust 0.9.65 (http://faust.grame.fr)


namespace colbwah {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	int 	iVec0[2];
	int 	iConst0;
	double 	fConst1;
	double 	fConst2;
	double 	fConst3;
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	double 	fConst4;
	double 	fRec2[2];
	double 	fRec1[2];
	double 	fRec0[2];
	double 	fConst5;
	double 	fConst6;
	double 	fRec4[2];
	double 	fConst7;
	double 	fConst8;
	double 	fRec3[2];
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	double 	fRec5[2];
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	double 	fConst9;
	double 	fConst10;
	double 	fConst11;
	double 	fConst12;
	double 	fConst13;
	double 	fConst14;
	double 	fConst15;
	double 	fConst16;
	double 	fConst17;
	double 	fConst18;
	double 	fConst19;
	double 	fConst20;
	double 	fConst21;
	double 	fConst22;
	double 	fConst23;
	double 	fConst24;
	double 	fConst25;
	double 	fConst26;
	double 	fConst27;
	double 	fConst28;
	double 	fConst29;
	double 	fConst30;
	double 	fConst31;
	double 	fConst32;
	double 	fConst33;
	double 	fConst34;
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT	*fslider3_;
	double 	fConst35;
	double 	fConst36;
	double 	fConst37;
	double 	fVec1[2];
	double 	fConst38;
	double 	fConst39;
	double 	fRec7[2];
	double 	fRec6[5];
	double 	fConst40;
	double 	fConst41;
	double 	fConst42;
	double 	fConst43;
	double 	fConst44;
	double 	fConst45;
	double 	fConst46;
	double 	fConst47;
	double 	fConst48;
	double 	fConst49;
	double 	fConst50;
	double 	fConst51;
	double 	fConst52;
	double 	fConst53;
	double 	fConst54;
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
	for (int i=0; i<2; i++) iVec0[i] = 0;
	for (int i=0; i<2; i++) fRec2[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec7[i] = 0;
	for (int i=0; i<5; i++) fRec6[i] = 0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	iConst0 = min(192000, max(1, fSamplingFreq));
	fConst1 = double(iConst0);
	fConst2 = (6.5528601067591e-21 * fConst1);
	fConst3 = (5.83881532956283e-13 + (fConst1 * (1.8780340503575e-14 + (fConst1 * (2.74563396261683e-18 + fConst2)))));
	fConst4 = (0.10471975511965977 / double(iConst0));
	fConst5 = exp((0 - (1e+01 / double(iConst0))));
	fConst6 = (1.0 - fConst5);
	fConst7 = exp((0 - (1e+02 / double(iConst0))));
	fConst8 = (1.0 - fConst7);
	fConst9 = (6.97503428259418e-20 * fConst1);
	fConst10 = ((fConst1 * ((fConst1 * (0 - (5.39620091780675e-18 + fConst9))) - 3.42307552972106e-15)) - 3.4676044717882e-14);
	fConst11 = (3.97898188862218e-19 * fConst1);
	fConst12 = (1.04378397231604e-13 + (fConst1 * (2.93048706029115e-15 + (fConst1 * (2.67097118338883e-17 + fConst11)))));
	fConst13 = (2.6706830774037e-21 * fConst1);
	fConst14 = (1.00293349888753e-13 + (fConst1 * ((fConst1 * (1.27578229328233e-17 - fConst13)) - 1.93436893661132e-14)));
	fConst15 = (8.31690116887645e-22 * fConst1);
	fConst16 = (fConst1 * (4.28499923433696e-15 + (fConst1 * (fConst15 - 3.20379811195304e-18))));
	fConst17 = (8.23016292634919e-22 * fConst1);
	fConst18 = (9.2036968791553e-14 + (fConst1 * ((fConst1 * (3.18413428804882e-18 - fConst17)) - 4.30254138569803e-15)));
	fConst19 = ((fConst1 * (1.8780340503575e-14 + (fConst1 * (fConst2 - 2.74563396261683e-18)))) - 5.83881532956283e-13);
	fConst20 = (3.4676044717882e-14 + (fConst1 * ((fConst1 * (5.39620091780675e-18 - fConst9)) - 3.42307552972106e-15)));
	fConst21 = ((fConst1 * (2.93048706029115e-15 + (fConst1 * (fConst11 - 2.67097118338883e-17)))) - 1.04378397231604e-13);
	fConst22 = (2.62114404270364e-20 * fConst1);
	fConst23 = faustpower<2>(fConst1);
	fConst24 = ((fConst23 * (5.49126792523366e-18 - fConst22)) - 1.16776306591257e-12);
	fConst25 = (2.79001371303767e-19 * fConst1);
	fConst26 = (6.9352089435764e-14 + (fConst23 * (fConst25 - 1.07924018356135e-17)));
	fConst27 = (1.59159275544887e-18 * fConst1);
	fConst28 = ((fConst23 * (5.34194236677766e-17 - fConst27)) - 2.08756794463207e-13);
	fConst29 = (6.84615105944212e-15 - (4.18502056955651e-19 * fConst23));
	fConst30 = ((2.38738913317331e-18 * fConst23) - 5.8609741205823e-15);
	fConst31 = ((3.93171606405546e-20 * fConst23) - 3.75606810071501e-14);
	fConst32 = (1.16776306591257e-12 + (fConst23 * (0 - (5.49126792523366e-18 + fConst22))));
	fConst33 = ((fConst23 * (1.07924018356135e-17 + fConst25)) - 6.9352089435764e-14);
	fConst34 = (2.08756794463207e-13 + (fConst23 * (0 - (5.34194236677766e-17 + fConst27))));
	fConst35 = (493.6899529387045 / double(iConst0));
	fConst36 = (1 + fConst35);
	fConst37 = (0.01 / fConst36);
	fConst38 = (1 - fConst35);
	fConst39 = (1.0 / fConst36);
	fConst40 = (1.06827323096148e-20 * fConst1);
	fConst41 = (2.00586699777507e-13 + (fConst23 * (fConst40 - 2.55156458656466e-17)));
	fConst42 = (3.32676046755058e-21 * fConst1);
	fConst43 = (fConst23 * (6.40759622390608e-18 - fConst42));
	fConst44 = (3.29206517053968e-21 * fConst1);
	fConst45 = (1.84073937583106e-13 + (fConst23 * (fConst44 - 6.36826857609764e-18)));
	fConst46 = (3.86873787322263e-14 - (1.60240984644222e-20 * fConst23));
	fConst47 = ((4.99014070132587e-21 * fConst23) - 8.56999846867392e-15);
	fConst48 = (8.60508277139606e-15 - (4.93809775580952e-21 * fConst23));
	fConst49 = ((fConst23 * (2.55156458656466e-17 + fConst40)) - 2.00586699777507e-13);
	fConst50 = (fConst23 * (0 - (6.40759622390608e-18 + fConst42)));
	fConst51 = ((fConst23 * (6.36826857609764e-18 + fConst44)) - 1.84073937583106e-13);
	fConst52 = ((fConst1 * ((fConst1 * (0 - (1.27578229328233e-17 + fConst13))) - 1.93436893661132e-14)) - 1.00293349888753e-13);
	fConst53 = (fConst1 * (4.28499923433696e-15 + (fConst1 * (3.20379811195304e-18 + fConst15))));
	fConst54 = ((fConst1 * ((fConst1 * (0 - (3.18413428804882e-18 + fConst17))) - 4.30254138569803e-15)) - 9.2036968791553e-14);
	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
#define fslider0 (*fslider0_)
#define fslider1 (*fslider1_)
#define fslider2 (*fslider2_)
#define fslider3 (*fslider3_)
	double 	fSlow0 = (fConst4 * double(fslider0));
	double 	fSlow1 = (4.748558434412966e-05 * (exp((5 * (1 - max(0.01, double(fslider1))))) - 1));
	int 	iSlow2 = int(double(fslider2));
	double 	fSlow3 = double(fslider3);
	double 	fSlow4 = (fConst37 * fSlow3);
	double 	fSlow5 = (0.01 * fSlow3);
	double 	fSlow6 = (1 - fSlow5);
	for (int i=0; i<count; i++) {
		iVec0[0] = 1;
		fRec2[0] = (fRec2[1] + (fSlow0 * (0 - fRec0[1])));
		fRec1[0] = ((1 + (fRec1[1] + (fSlow0 * fRec2[0]))) - iVec0[1]);
		fRec0[0] = fRec1[0];
		double fTemp0 = (double)input0[i];
		double fTemp1 = fabs(fTemp0);
		fRec4[0] = ((fConst5 * max(fTemp1, fRec4[1])) + (fConst6 * fTemp1));
		fRec3[0] = ((fConst7 * fRec3[1]) + (fConst8 * fRec4[0]));
		fRec5[0] = ((0.993 * fRec5[1]) + fSlow1);
		double fTemp2 = ((iSlow2==0)? fRec5[0] : ((iSlow2==1)?max(0.02, min((double)1, fRec3[0])):(1 - max(0.02, min(0.98, (0.5 * (1 + fRec0[0])))))) );
		double fTemp3 = (2.41228015122866e-12 + (fConst1 * ((fTemp2 * (fConst12 + (fConst10 * fTemp2))) + fConst3)));
		fVec1[0] = (fSlow4 * fTemp0);
		fRec7[0] = ((fConst39 * ((fSlow5 * fTemp0) + (fConst38 * fRec7[1]))) - fVec1[1]);
		fRec6[0] = (fRec7[0] - (((((fRec6[1] * (9.64912060491465e-12 + (fConst1 * ((fTemp2 * (fConst34 + (fConst33 * fTemp2))) + fConst32)))) + (fRec6[2] * (1.4473680907372e-11 + (fConst23 * (fConst31 + (fTemp2 * (fConst30 + (fConst29 * fTemp2)))))))) + (fRec6[3] * (9.64912060491465e-12 + (fConst1 * ((fTemp2 * (fConst28 + (fConst26 * fTemp2))) + fConst24))))) + (fRec6[4] * (2.41228015122866e-12 + (fConst1 * ((fTemp2 * (fConst21 + (fConst20 * fTemp2))) + fConst19))))) / fTemp3));
		output0[i] = (FAUSTFLOAT)((fSlow6 * fTemp0) + (fConst1 * ((((((fRec6[0] * ((fTemp2 * (fConst54 + (fConst53 * fTemp2))) + fConst52)) + (fRec6[1] * ((fTemp2 * (fConst51 + (fConst50 * fTemp2))) + fConst49))) + (fConst1 * (fRec6[2] * ((fTemp2 * (fConst48 + (fConst47 * fTemp2))) + fConst46)))) + (fRec6[3] * ((fTemp2 * (fConst45 + (fConst43 * fTemp2))) + fConst41))) + (fRec6[4] * ((fTemp2 * (fConst18 + (fConst16 * fTemp2))) + fConst14))) / fTemp3)));
		// post processing
		for (int i=4; i>0; i--) fRec6[i] = fRec6[i-1];
		fRec7[1] = fRec7[0];
		fVec1[1] = fVec1[0];
		fRec5[1] = fRec5[0];
		fRec3[1] = fRec3[0];
		fRec4[1] = fRec4[0];
		fRec0[1] = fRec0[0];
		fRec1[1] = fRec1[0];
		fRec2[1] = fRec2[0];
		iVec0[1] = iVec0[0];
	}

#undef fslider0
#undef fslider1
#undef fslider2
#undef fslider3
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	fslider1_ = reg.registerVar("wah.Wah","","SA","",&fslider1, 0.0, 0.0, 1.0, 0.01);
	fslider0_ = reg.registerVar("wah.freq",N_("Alien Freq"),"SA",N_("LFO in Beats per Minute"),&fslider0, 24.0, 24.0, 3.6e+02, 1.0);
	static const value_pair fslider2_values[] = {{"manual"},{"auto"},{"alien"},{0}};
	fslider2_ = reg.registerSharedEnumVar("wah.mode","","SA","",fslider2_values,&fslider2, 0.0, 0.0, 2.0, 1.0);
	fslider3_ = reg.registerVar("wah.wet_dry",N_("dry/wet"),"SA","",&fslider3, 1e+02, 0.0, 1e+02, 1.0);
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
