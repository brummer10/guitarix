// generated from file '../src/faust/foxwah.dsp' by dsp2cc:
// Code generated with Faust 0.9.65 (http://faust.grame.fr)


namespace foxwah {

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
	double 	fRec5[2];
	double 	fConst7;
	double 	fConst8;
	double 	fRec4[2];
	double 	fRec3[2];
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	double 	fRec6[2];
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
	double 	fRec8[2];
	double 	fRec7[5];
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
	id = "foxwah";
	name = N_("Foxx Wah");
	groups = 0;
	description = N_("Foxx Wah"); // description (tooltip)
	category = N_("Guitar Effects");       // category
	shortname = N_("Foxx Wah");     // shortname
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
	for (int i=0; i<2; i++) fRec5[i] = 0;
	for (int i=0; i<2; i++) fRec4[i] = 0;
	for (int i=0; i<2; i++) fRec3[i] = 0;
	for (int i=0; i<2; i++) fRec6[i] = 0;
	for (int i=0; i<2; i++) fVec1[i] = 0;
	for (int i=0; i<2; i++) fRec8[i] = 0;
	for (int i=0; i<5; i++) fRec7[i] = 0;
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
	fConst2 = (3.06896988210923e-19 * fConst1);
	fConst3 = (8.49404844378593e-12 + (fConst1 * (2.93439745158876e-13 + (fConst1 * (2.40276998984285e-17 + fConst2)))));
	fConst4 = (0.10471975511965977 / double(iConst0));
	fConst5 = exp((0 - (1e+01 / double(iConst0))));
	fConst6 = (1.0 - fConst5);
	fConst7 = exp((0 - (1e+02 / double(iConst0))));
	fConst8 = (1.0 - fConst7);
	fConst9 = (5.27939482245346e-20 * fConst1);
	fConst10 = (fConst1 * ((fConst1 * (0 - (3.84581222788281e-18 + fConst9))) - 4.45118937547182e-14));
	fConst11 = (2.11837046611975e-19 * fConst1);
	fConst12 = ((fConst1 * (5.84262202161266e-14 + (fConst1 * (0 - (1.50671579237021e-18 + fConst11))))) - 1.12403772107874e-12);
	fConst13 = (7.06526492747902e-21 * fConst1);
	fConst14 = (3.24292143859646e-12 + (fConst1 * ((fConst1 * (2.33820876003629e-16 - fConst13)) - 3.26825644515106e-13)));
	fConst15 = (1.83199828084009e-21 * fConst1);
	fConst16 = (fConst1 * (5.9658637492238e-14 + (fConst1 * (fConst15 - 4.37177575394138e-17))));
	fConst17 = (2.03749178510912e-21 * fConst1);
	fConst18 = ((fConst1 * ((fConst1 * (4.85447818408113e-17 - fConst17)) - 6.52701543961359e-14)) - 1.41209804493283e-12);
	fConst19 = ((fConst1 * (2.93439745158876e-13 + (fConst1 * (fConst2 - 2.40276998984285e-17)))) - 8.49404844378593e-12);
	fConst20 = (fConst1 * ((fConst1 * (3.84581222788281e-18 - fConst9)) - 4.45118937547182e-14));
	fConst21 = (1.12403772107874e-12 + (fConst1 * (5.84262202161266e-14 + (fConst1 * (1.50671579237021e-18 - fConst11)))));
	fConst22 = (1.22758795284369e-18 * fConst1);
	fConst23 = faustpower<2>(fConst1);
	fConst24 = ((fConst23 * (4.80553997968569e-17 - fConst22)) - 1.69880968875719e-11);
	fConst25 = (2.11175792898138e-19 * fConst1);
	fConst26 = (fConst23 * (fConst25 - 7.69162445576562e-18));
	fConst27 = (8.473481864479e-19 * fConst1);
	fConst28 = (2.24807544215749e-12 + (fConst23 * (fConst27 - 3.01343158474042e-18)));
	fConst29 = (8.90237875094365e-14 - (3.16763689347207e-19 * fConst23));
	fConst30 = (0 - (1.16852440432253e-13 + (1.27102227967185e-18 * fConst23)));
	fConst31 = ((1.84138192926554e-18 * fConst23) - 5.86879490317752e-13);
	fConst32 = (1.69880968875719e-11 + (fConst23 * (0 - (4.80553997968569e-17 + fConst22))));
	fConst33 = (fConst23 * (7.69162445576562e-18 + fConst25));
	fConst34 = ((fConst23 * (3.01343158474042e-18 + fConst27)) - 2.24807544215749e-12);
	fConst35 = (717.0124850323367 / double(iConst0));
	fConst36 = (1 + fConst35);
	fConst37 = (0.01 / fConst36);
	fConst38 = (1 - fConst35);
	fConst39 = (1.0 / fConst36);
	fConst40 = (2.82610597099161e-20 * fConst1);
	fConst41 = (6.48584287719292e-12 + (fConst23 * (fConst40 - 4.67641752007259e-16)));
	fConst42 = (7.32799312336037e-21 * fConst1);
	fConst43 = (fConst23 * (8.74355150788276e-17 - fConst42));
	fConst44 = (8.14996714043648e-21 * fConst1);
	fConst45 = ((fConst23 * (fConst44 - 9.70895636816225e-17)) - 2.82419608986565e-12);
	fConst46 = (6.53651289030211e-13 - (4.23915895648741e-20 * fConst23));
	fConst47 = ((1.09919896850405e-20 * fConst23) - 1.19317274984476e-13);
	fConst48 = (1.30540308792272e-13 - (1.22249507106547e-20 * fConst23));
	fConst49 = ((fConst23 * (4.67641752007259e-16 + fConst40)) - 6.48584287719292e-12);
	fConst50 = (fConst23 * (0 - (8.74355150788276e-17 + fConst42)));
	fConst51 = (2.82419608986565e-12 + (fConst23 * (9.70895636816225e-17 + fConst44)));
	fConst52 = ((fConst1 * ((fConst1 * (0 - (2.33820876003629e-16 + fConst13))) - 3.26825644515106e-13)) - 3.24292143859646e-12);
	fConst53 = (fConst1 * (5.9658637492238e-14 + (fConst1 * (4.37177575394138e-17 + fConst15))));
	fConst54 = (1.41209804493283e-12 + (fConst1 * ((fConst1 * (0 - (4.85447818408113e-17 + fConst17))) - 6.52701543961359e-14)));
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
	double 	fSlow1 = (4.748558434412966e-05 * (exp((5 * max(0.01, double(fslider1)))) - 1));
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
		fRec5[0] = ((fConst5 * max(fTemp1, fRec5[1])) + (fConst6 * fTemp1));
		fRec4[0] = ((fConst7 * fRec4[1]) + (fConst8 * fRec5[0]));
		fRec3[0] = ((0.993 * fRec3[1]) + (0.007000000000000006 * (1 - max(0.02, min(0.98, fRec4[0])))));
		fRec6[0] = ((0.993 * fRec6[1]) + fSlow1);
		double fTemp2 = ((iSlow2==0)? fRec6[0] : ((iSlow2==1)?fRec3[0]:(1 - max(0.02, min(0.98, (0.5 * (1 + fRec0[0])))))) );
		double fTemp3 = (2.83847909363319e-11 + (fConst1 * ((fTemp2 * (fConst12 + (fConst10 * fTemp2))) + fConst3)));
		fVec1[0] = (fSlow4 * fTemp0);
		fRec8[0] = ((fConst39 * ((fSlow5 * fTemp0) + (fConst38 * fRec8[1]))) - fVec1[1]);
		fRec7[0] = (fRec8[0] - (((((fRec7[1] * (1.13539163745328e-10 + (fConst1 * ((fTemp2 * (fConst34 + (fConst33 * fTemp2))) + fConst32)))) + (fRec7[2] * (1.70308745617991e-10 + (fConst23 * (fConst31 + (fTemp2 * (fConst30 + (fConst29 * fTemp2)))))))) + (fRec7[3] * (1.13539163745328e-10 + (fConst1 * ((fTemp2 * (fConst28 + (fConst26 * fTemp2))) + fConst24))))) + (fRec7[4] * (2.83847909363319e-11 + (fConst1 * ((fTemp2 * (fConst21 + (fConst20 * fTemp2))) + fConst19))))) / fTemp3));
		output0[i] = (FAUSTFLOAT)((fSlow6 * fTemp0) + (fConst1 * ((((((fRec7[0] * ((fTemp2 * (fConst54 + (fConst53 * fTemp2))) + fConst52)) + (fRec7[1] * ((fTemp2 * (fConst51 + (fConst50 * fTemp2))) + fConst49))) + (fConst1 * (fRec7[2] * ((fTemp2 * (fConst48 + (fConst47 * fTemp2))) + fConst46)))) + (fRec7[3] * ((fTemp2 * (fConst45 + (fConst43 * fTemp2))) + fConst41))) + (fRec7[4] * ((fTemp2 * (fConst18 + (fConst16 * fTemp2))) + fConst14))) / fTemp3)));
		// post processing
		for (int i=4; i>0; i--) fRec7[i] = fRec7[i-1];
		fRec8[1] = fRec8[0];
		fVec1[1] = fVec1[0];
		fRec6[1] = fRec6[0];
		fRec3[1] = fRec3[0];
		fRec4[1] = fRec4[0];
		fRec5[1] = fRec5[0];
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

} // end namespace foxwah
