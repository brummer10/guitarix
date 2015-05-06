// generated from file '../src/faust/dallaswah.dsp' by dsp2cc:
// Code generated with Faust 0.9.65 (http://faust.grame.fr)


namespace dallaswah {

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
	double 	fConst35;
	double 	fConst36;
	double 	fConst37;
	double 	fConst38;
	double 	fConst39;
	double 	fConst40;
	double 	fConst41;
	double 	fConst42;
	double 	fConst43;
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT	*fslider3_;
	double 	fRec6[7];
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
	double 	fConst55;
	double 	fConst56;
	double 	fConst57;
	double 	fConst58;
	double 	fConst59;
	double 	fConst60;
	double 	fConst61;
	double 	fConst62;
	double 	fConst63;
	double 	fConst64;
	double 	fConst65;
	double 	fConst66;
	double 	fConst67;
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
	id = "dallaswah";
	name = N_("Dallas Wah");
	groups = 0;
	description = N_("Dallas Arbiter Wah"); // description (tooltip)
	category = N_("Guitar Effects");       // category
	shortname = N_("Dallas  Wah");     // shortname
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
	for (int i=0; i<7; i++) fRec6[i] = 0;
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
	fConst2 = (2.51617848419225e-29 * fConst1);
	fConst3 = (1.13711463931101e-15 + (fConst1 * (3.6815416628337e-16 + (fConst1 * (3.59986998986588e-17 + (fConst1 * (1.09351207812161e-18 + (fConst1 * (6.29629967279172e-22 + (fConst1 * (8.09025818356709e-26 + fConst2)))))))))));
	fConst4 = (0.10471975511965977 / double(iConst0));
	fConst5 = exp((0 - (1e+01 / double(iConst0))));
	fConst6 = (1.0 - fConst5);
	fConst7 = exp((0 - (1e+02 / double(iConst0))));
	fConst8 = (1.0 - fConst7);
	fConst9 = (1.86565797488138e-29 * fConst1);
	fConst10 = (1.52896089528608e-31 + (fConst1 * ((fConst1 * ((fConst1 * ((fConst1 * (0 - (4.23676337082129e-26 + fConst9))) - 1.00468221585939e-22)) - 1.65639280522528e-19)) - 1.59055047288262e-18)));
	fConst11 = (1.14266706841096e-28 * fConst1);
	fConst12 = (4.25280875102305e-17 + (fConst1 * (5.68607004495272e-18 + (fConst1 * (1.35174012417023e-19 + (fConst1 * (9.3225622428148e-23 + (fConst1 * (2.27871736066328e-25 + fConst11)))))))));
	fConst13 = (2.95334143650199e-30 * fConst1);
	fConst14 = ((fConst1 * (2.71762597345689e-20 + (fConst1 * ((fConst1 * (2.39932288230564e-25 - fConst13)) - 3.60669905407753e-22)))) - 1.62378538408517e-19);
	fConst15 = (1.20894405825314e-30 * fConst1);
	fConst16 = ((fConst1 * ((fConst1 * (6.67221502794578e-23 + (fConst1 * (fConst15 - 4.55223559536905e-26)))) - 4.60832615818034e-21)) - 4.42988173510265e-34);
	fConst17 = (9.90901628275927e-31 * fConst1);
	fConst18 = ((fConst1 * (5.22251274319268e-21 + (fConst1 * ((fConst1 * (3.74994304179366e-26 - fConst17)) - 5.59001169449057e-23)))) - 9.86965379369583e-20);
	fConst19 = (1.13711463931101e-15 + (fConst1 * ((fConst1 * (3.59986998986588e-17 + (fConst1 * ((fConst1 * (6.29629967279172e-22 + (fConst1 * (fConst2 - 8.09025818356709e-26)))) - 1.09351207812161e-18)))) - 3.6815416628337e-16)));
	fConst20 = ((fConst1 * ((fConst1 * (1.65639280522528e-19 + (fConst1 * ((fConst1 * (4.23676337082129e-26 - fConst9)) - 1.00468221585939e-22)))) - 1.59055047288262e-18)) - 1.52896089528608e-31);
	fConst21 = ((fConst1 * (5.68607004495272e-18 + (fConst1 * ((fConst1 * (9.3225622428148e-23 + (fConst1 * (fConst11 - 2.27871736066328e-25)))) - 1.35174012417023e-19)))) - 4.25280875102305e-17);
	fConst22 = (1.50970709051535e-28 * fConst1);
	fConst23 = faustpower<2>(fConst1);
	fConst24 = (6.82268783586605e-15 + (fConst1 * ((fConst1 * (7.19973997973176e-17 + (fConst23 * ((fConst1 * (3.23610327342684e-25 - fConst22)) - 1.25925993455834e-21)))) - 1.47261666513348e-15)));
	fConst25 = (1.11939478492883e-28 * fConst1);
	fConst26 = ((fConst1 * ((fConst23 * (2.00936443171878e-22 + (fConst1 * (fConst25 - 1.69470534832851e-25)))) - 3.18110094576525e-18)) - 6.11584358114433e-31);
	fConst27 = (6.85600241046577e-28 * fConst1);
	fConst28 = ((fConst1 * (1.13721400899054e-17 + (fConst23 * ((fConst1 * (9.1148694426531e-25 - fConst27)) - 1.86451244856296e-22)))) - 1.70112350040922e-16);
	fConst29 = (3.77426772628837e-28 * fConst1);
	fConst30 = (1.70567195896651e-14 + (fConst1 * ((fConst1 * ((fConst1 * (3.28053623436483e-18 + (fConst1 * ((fConst1 * (fConst29 - 4.04512909178355e-25)) - 6.29629967279172e-22)))) - 3.59986998986588e-17)) - 1.84077083141685e-15)));
	fConst31 = (2.79848696232207e-28 * fConst1);
	fConst32 = ((fConst1 * (1.59055047288262e-18 + (fConst1 * ((fConst1 * (1.00468221585939e-22 + (fConst1 * (2.11838168541064e-25 - fConst31)))) - 4.96917841567585e-19)))) - 7.64480447643042e-31);
	fConst33 = (1.71400060261644e-27 * fConst1);
	fConst34 = ((fConst1 * ((fConst1 * (4.05522037251071e-19 + (fConst1 * ((fConst1 * (fConst33 - 1.13935868033164e-24)) - 9.3225622428148e-23)))) - 5.68607004495272e-18)) - 2.12640437551152e-16);
	fConst35 = (2.27422927862202e-14 + (fConst23 * ((fConst23 * (2.51851986911669e-21 - (5.03235696838449e-28 * fConst23))) - 1.43994799594635e-16)));
	fConst36 = (6.3622018915305e-18 + (fConst23 * ((3.73131594976276e-28 * fConst23) - 4.01872886343757e-22)));
	fConst37 = ((fConst23 * (3.72902489712592e-22 - (2.28533413682192e-27 * fConst23))) - 2.27442801798109e-17);
	fConst38 = (1.70567195896651e-14 + (fConst1 * (1.84077083141685e-15 + (fConst1 * ((fConst1 * ((fConst1 * ((fConst1 * (4.04512909178355e-25 + fConst29)) - 6.29629967279172e-22)) - 3.28053623436483e-18)) - 3.59986998986588e-17)))));
	fConst39 = (7.64480447643042e-31 + (fConst1 * (1.59055047288262e-18 + (fConst1 * (4.96917841567585e-19 + (fConst1 * (1.00468221585939e-22 + (fConst1 * (0 - (2.11838168541064e-25 + fConst31))))))))));
	fConst40 = (2.12640437551152e-16 + (fConst1 * ((fConst1 * ((fConst1 * ((fConst1 * (1.13935868033164e-24 + fConst33)) - 9.3225622428148e-23)) - 4.05522037251071e-19)) - 5.68607004495272e-18)));
	fConst41 = (6.82268783586605e-15 + (fConst1 * (1.47261666513348e-15 + (fConst1 * (7.19973997973176e-17 + (fConst23 * ((fConst1 * (0 - (3.23610327342684e-25 + fConst22))) - 1.25925993455834e-21)))))));
	fConst42 = (6.11584358114433e-31 + (fConst1 * ((fConst23 * (2.00936443171878e-22 + (fConst1 * (1.69470534832851e-25 + fConst25)))) - 3.18110094576525e-18)));
	fConst43 = (1.70112350040922e-16 + (fConst1 * (1.13721400899054e-17 + (fConst23 * ((fConst1 * (0 - (9.1148694426531e-25 + fConst27))) - 1.86451244856296e-22)))));
	fConst44 = (1.77200486190119e-29 * fConst1);
	fConst45 = ((fConst23 * (7.21339810815506e-22 + (fConst1 * (fConst44 - 9.59729152922254e-25)))) - 3.24757076817034e-19);
	fConst46 = (7.25366434951886e-30 * fConst1);
	fConst47 = ((fConst23 * ((fConst1 * (1.82089423814762e-25 - fConst46)) - 1.33444300558916e-22)) - 8.85976347020531e-34);
	fConst48 = (5.94540976965556e-30 * fConst1);
	fConst49 = ((fConst23 * (1.11800233889811e-22 + (fConst1 * (fConst48 - 1.49997721671747e-25)))) - 1.97393075873917e-19);
	fConst50 = (4.43001215475298e-29 * fConst1);
	fConst51 = (1.62378538408517e-19 + (fConst1 * ((fConst1 * (3.60669905407753e-22 + (fConst1 * (1.19966144115282e-24 - fConst50)))) - 8.15287792037067e-20)));
	fConst52 = (1.81341608737971e-29 * fConst1);
	fConst53 = (4.42988173510265e-34 + (fConst1 * (1.3824978474541e-20 + (fConst1 * ((fConst1 * (fConst52 - 2.27611779768452e-25)) - 6.67221502794578e-23)))));
	fConst54 = (1.48635244241389e-29 * fConst1);
	fConst55 = (9.86965379369583e-20 + (fConst1 * ((fConst1 * (5.59001169449057e-23 + (fConst1 * (1.87497152089683e-25 - fConst54)))) - 1.5667538229578e-20)));
	fConst56 = (6.49514153634068e-19 + (fConst23 * ((5.90668287300397e-29 * fConst23) - 1.44267962163101e-21)));
	fConst57 = (1.77195269404106e-33 + (fConst23 * (2.66888601117831e-22 - (2.41788811650629e-29 * fConst23))));
	fConst58 = (3.94786151747833e-19 + (fConst23 * ((1.98180325655185e-29 * fConst23) - 2.23600467779623e-22)));
	fConst59 = (1.62378538408517e-19 + (fConst1 * (8.15287792037067e-20 + (fConst1 * (3.60669905407753e-22 + (fConst1 * (0 - (1.19966144115282e-24 + fConst50))))))));
	fConst60 = (4.42988173510265e-34 + (fConst1 * ((fConst1 * ((fConst1 * (2.27611779768452e-25 + fConst52)) - 6.67221502794578e-23)) - 1.3824978474541e-20)));
	fConst61 = (9.86965379369583e-20 + (fConst1 * (1.5667538229578e-20 + (fConst1 * (5.59001169449057e-23 + (fConst1 * (0 - (1.87497152089683e-25 + fConst54))))))));
	fConst62 = ((fConst23 * (7.21339810815506e-22 + (fConst1 * (9.59729152922254e-25 + fConst44)))) - 3.24757076817034e-19);
	fConst63 = ((fConst23 * ((fConst1 * (0 - (1.82089423814762e-25 + fConst46))) - 1.33444300558916e-22)) - 8.85976347020531e-34);
	fConst64 = ((fConst23 * (1.11800233889811e-22 + (fConst1 * (1.49997721671747e-25 + fConst48)))) - 1.97393075873917e-19);
	fConst65 = ((fConst1 * ((fConst1 * ((fConst1 * (0 - (2.39932288230564e-25 + fConst13))) - 3.60669905407753e-22)) - 2.71762597345689e-20)) - 1.62378538408517e-19);
	fConst66 = ((fConst1 * (4.60832615818034e-21 + (fConst1 * (6.67221502794578e-23 + (fConst1 * (4.55223559536905e-26 + fConst15)))))) - 4.42988173510265e-34);
	fConst67 = ((fConst1 * ((fConst1 * ((fConst1 * (0 - (3.74994304179366e-26 + fConst17))) - 5.59001169449057e-23)) - 5.22251274319268e-21)) - 9.86965379369583e-20);
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
	double 	fSlow3 = (0.01 * double(fslider3));
	double 	fSlow4 = (1 - fSlow3);
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
		double fTemp3 = ((fTemp2 * ((fConst1 * (fConst12 + (fConst10 * fTemp2))) - 4.08813073605905e-30)) + fConst3);
		fRec6[0] = ((fSlow3 * fTemp0) - (((((((fRec6[1] * ((fTemp2 * ((fConst1 * (fConst43 + (fConst42 * fTemp2))) - 2.45287844163543e-29)) + fConst41)) + (fRec6[2] * ((fTemp2 * ((fConst1 * (fConst40 + (fConst39 * fTemp2))) - 6.13219610408857e-29)) + fConst38))) + (fRec6[3] * ((fTemp2 * ((fConst23 * (fConst37 + (fConst36 * fTemp2))) - 8.17626147211809e-29)) + fConst35))) + (fRec6[4] * ((fTemp2 * ((fConst1 * (fConst34 + (fConst32 * fTemp2))) - 6.13219610408857e-29)) + fConst30))) + (fRec6[5] * ((fTemp2 * ((fConst1 * (fConst28 + (fConst26 * fTemp2))) - 2.45287844163543e-29)) + fConst24))) + (fRec6[6] * ((fTemp2 * ((fConst1 * (fConst21 + (fConst20 * fTemp2))) - 4.08813073605905e-30)) + fConst19))) / fTemp3));
		output0[i] = (FAUSTFLOAT)((fSlow4 * fTemp0) + (fConst23 * ((((((((fRec6[0] * ((fTemp2 * (fConst67 + (fConst66 * fTemp2))) + fConst65)) + (fRec6[1] * ((fTemp2 * (fConst64 + (fConst63 * fTemp2))) + fConst62))) + (fRec6[2] * ((fTemp2 * (fConst61 + (fConst60 * fTemp2))) + fConst59))) + (fRec6[3] * ((fTemp2 * (fConst58 + (fConst57 * fTemp2))) + fConst56))) + (fRec6[4] * ((fTemp2 * (fConst55 + (fConst53 * fTemp2))) + fConst51))) + (fRec6[5] * ((fTemp2 * (fConst49 + (fConst47 * fTemp2))) + fConst45))) + (fRec6[6] * ((fTemp2 * (fConst18 + (fConst16 * fTemp2))) + fConst14))) / fTemp3)));
		// post processing
		for (int i=6; i>0; i--) fRec6[i] = fRec6[i-1];
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

} // end namespace dallaswah
