// generated from file '../src/faust/dallaswah.dsp' by dsp2cc:
// Code generated with Faust 0.9.90 (http://faust.grame.fr)


namespace dallaswah {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	int 	iVec0[2];
	FAUSTFLOAT 	fslider0;
	FAUSTFLOAT	*fslider0_;
	double 	fConst0;
	double 	fConst1;
	double 	fRec2[2];
	double 	fRec1[2];
	double 	fRec0[2];
	double 	fConst2;
	double 	fConst3;
	double 	fRec5[2];
	double 	fConst4;
	double 	fConst5;
	double 	fRec4[2];
	double 	fRec3[2];
	FAUSTFLOAT 	fslider1;
	FAUSTFLOAT	*fslider1_;
	double 	fRec6[2];
	FAUSTFLOAT 	fslider2;
	FAUSTFLOAT	*fslider2_;
	double 	fConst6;
	double 	fConst7;
	double 	fConst8;
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
	fConst0 = min(1.92e+05, max(1.0, (double)fSamplingFreq));
	fConst1 = (0.10471975511965977 / fConst0);
	fConst2 = exp((0 - (1e+01 / fConst0)));
	fConst3 = (1.0 - fConst2);
	fConst4 = exp((0 - (1e+02 / fConst0)));
	fConst5 = (1.0 - fConst4);
	fConst6 = double(fConst0);
	fConst7 = (4.47972527031659e-20 * fConst6);
	fConst8 = (2.01493666656321e-26 + (fConst6 * ((fConst6 * (0 - (1.0922674147551e-17 + fConst7))) - 2.09610231217262e-13)));
	fConst9 = (2.74906060407121e-19 * fConst6);
	fConst10 = (5.60455163682517e-12 + (fConst6 * (1.4198849343527e-13 + (fConst6 * (2.45407810123387e-17 + fConst9)))));
	fConst11 = (6.05097478328861e-20 * fConst6);
	fConst12 = (1.49854321840248e-10 + (fConst6 * (3.46679367777423e-11 + (fConst6 * (1.39111781189056e-12 + (fConst6 * (3.86741226880994e-17 + fConst11)))))));
	fConst13 = (2.83510090714092e-21 * fConst6);
	fConst14 = (1.53357283072645e-26 + (fConst6 * (1.59534818623044e-13 + (fConst6 * (fConst13 - 1.04896968320146e-16)))));
	fConst15 = (2.32347860461171e-21 * fConst6);
	fConst16 = (3.41675778537176e-12 + (fConst6 * ((fConst6 * (8.64108311643329e-17 - fConst15)) - 1.33575525905195e-13)));
	fConst17 = (7.07917432005204e-21 * fConst6);
	fConst18 = (5.62135356398181e-12 + (fConst6 * ((fConst6 * (5.52389028989215e-16 - fConst17)) - 8.63117119019868e-13)));
	fConst19 = ((fConst6 * ((fConst6 * (1.0922674147551e-17 - fConst7)) - 2.09610231217262e-13)) - 2.01493666656321e-26);
	fConst20 = ((fConst6 * (1.4198849343527e-13 + (fConst6 * (fConst9 - 2.45407810123387e-17)))) - 5.60455163682517e-12);
	fConst21 = (1.49854321840248e-10 + (fConst6 * ((fConst6 * (1.39111781189056e-12 + (fConst6 * (fConst11 - 3.86741226880994e-17)))) - 3.46679367777423e-11)));
	fConst22 = (1.79189010812664e-19 * fConst6);
	fConst23 = faustpower<2>(fConst6);
	fConst24 = ((fConst23 * (fConst22 - 2.18453482951021e-17)) - 4.02987333312642e-26);
	fConst25 = (1.09962424162848e-18 * fConst6);
	fConst26 = ((fConst23 * (4.90815620246775e-17 - fConst25)) - 1.12091032736503e-11);
	fConst27 = (2.42038991331544e-19 * fConst6);
	fConst28 = (5.99417287360993e-10 + (fConst6 * ((fConst23 * (7.73482453761989e-17 - fConst27)) - 6.93358735554846e-11)));
	fConst29 = (4.19220462434524e-13 - (2.68783516218996e-19 * fConst23));
	fConst30 = ((1.64943636244273e-18 * fConst23) - 2.8397698687054e-13);
	fConst31 = (8.99125931041489e-10 + (fConst23 * ((3.63058486997317e-19 * fConst23) - 2.78223562378113e-12)));
	fConst32 = (4.02987333312642e-26 + (fConst23 * (2.18453482951021e-17 + fConst22)));
	fConst33 = (1.12091032736503e-11 + (fConst23 * (0 - (4.90815620246775e-17 + fConst25))));
	fConst34 = (5.99417287360993e-10 + (fConst6 * (6.93358735554846e-11 + (fConst23 * (0 - (7.73482453761989e-17 + fConst27))))));
	fConst35 = (1833.7929316777988 / fConst0);
	fConst36 = (1 + fConst35);
	fConst37 = (0.01 / fConst36);
	fConst38 = (1 - fConst35);
	fConst39 = (1.0 / fConst36);
	fConst40 = (1.13404036285637e-20 * fConst6);
	fConst41 = (3.06714566145289e-26 + (fConst23 * (2.09793936640293e-16 - fConst40)));
	fConst42 = (9.29391441844685e-21 * fConst6);
	fConst43 = (6.83351557074351e-12 + (fConst23 * (fConst42 - 1.72821662328666e-16)));
	fConst44 = (2.83166972802082e-20 * fConst6);
	fConst45 = (1.12427071279636e-11 + (fConst23 * (fConst44 - 1.10477805797843e-15)));
	fConst46 = ((1.70106054428455e-20 * fConst23) - 3.19069637246088e-13);
	fConst47 = (2.6715105181039e-13 - (1.39408716276703e-20 * fConst23));
	fConst48 = (1.72623423803974e-12 - (4.24750459203123e-20 * fConst23));
	fConst49 = ((fConst23 * (0 - (2.09793936640293e-16 + fConst40))) - 3.06714566145289e-26);
	fConst50 = ((fConst23 * (1.72821662328666e-16 + fConst42)) - 6.83351557074351e-12);
	fConst51 = ((fConst23 * (1.10477805797843e-15 + fConst44)) - 1.12427071279636e-11);
	fConst52 = ((fConst6 * (1.59534818623044e-13 + (fConst6 * (1.04896968320146e-16 + fConst13)))) - 1.53357283072645e-26);
	fConst53 = ((fConst6 * ((fConst6 * (0 - (8.64108311643329e-17 + fConst15))) - 1.33575525905195e-13)) - 3.41675778537176e-12);
	fConst54 = ((fConst6 * ((fConst6 * (0 - (5.52389028989215e-16 + fConst17))) - 8.63117119019868e-13)) - 5.62135356398181e-12);
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
	double 	fSlow0 = (fConst1 * double(fslider0));
	double 	fSlow1 = (4.748558434412966e-05 * (exp((5 * (1 - max(0.01, double(fslider1))))) - 1));
	int 	iSlow2 = int(double(fslider2));
	double 	fSlow3 = double(fslider3);
	double 	fSlow4 = (fConst37 * fSlow3);
	double 	fSlow5 = (0.01 * fSlow3);
	double 	fSlow6 = (1 - fSlow5);
	for (int i=0; i<count; i++) {
		iVec0[0] = 1;
		fRec2[0] = ((fSlow0 * (0 - fRec0[1])) + fRec2[1]);
		fRec1[0] = ((1 + (fRec1[1] + (fSlow0 * fRec2[0]))) - iVec0[1]);
		fRec0[0] = fRec1[0];
		double fTemp0 = (double)input0[i];
		double fTemp1 = fabs(fTemp0);
		fRec5[0] = max(fTemp1, ((fConst3 * fTemp1) + (fConst2 * fRec5[1])));
		fRec4[0] = ((fConst4 * fRec4[1]) + (fConst5 * fRec5[0]));
		fRec3[0] = ((0.993 * fRec3[1]) + (0.007000000000000006 * max(0.02, min((double)1, fRec4[0]))));
		fRec6[0] = (fSlow1 + (0.993 * fRec6[1]));
		double fTemp2 = ((iSlow2==0)? fRec6[0] : ((iSlow2==1)?fRec3[0]:(1 - max(0.02, min(0.98, (0.5 * (1 + fRec0[0])))))) );
		double fTemp3 = (fConst12 + (fTemp2 * ((fConst6 * (fConst10 + (fConst8 * fTemp2))) - 5.38753119401928e-25)));
		fVec1[0] = (fSlow4 * fTemp0);
		fRec8[0] = ((fConst39 * ((fSlow5 * fTemp0) + (fConst38 * fRec8[1]))) - fVec1[1]);
		fRec7[0] = (fRec8[0] - (((((fRec7[1] * (fConst34 + (fTemp2 * ((fConst6 * (fConst33 + (fConst32 * fTemp2))) - 2.15501247760771e-24)))) + (fRec7[2] * (fConst31 + (fTemp2 * ((fConst23 * (fConst30 + (fConst29 * fTemp2))) - 3.23251871641157e-24))))) + (fRec7[3] * (fConst28 + (fTemp2 * ((fConst6 * (fConst26 + (fConst24 * fTemp2))) - 2.15501247760771e-24))))) + (fRec7[4] * (fConst21 + (fTemp2 * ((fConst6 * (fConst20 + (fConst19 * fTemp2))) - 5.38753119401928e-25))))) / fTemp3));
		output0[i] = (FAUSTFLOAT)((fSlow6 * fTemp0) + (fConst6 * ((((((fRec7[0] * (fConst54 + (fTemp2 * (fConst53 + (fConst52 * fTemp2))))) + (fRec7[1] * (fConst51 + (fTemp2 * (fConst50 + (fConst49 * fTemp2)))))) + (fConst6 * (fRec7[2] * (fConst48 + (fTemp2 * (fConst47 + (fConst46 * fTemp2))))))) + (fRec7[3] * (fConst45 + (fTemp2 * (fConst43 + (fConst41 * fTemp2)))))) + (fRec7[4] * (fConst18 + (fTemp2 * (fConst16 + (fConst14 * fTemp2)))))) / fTemp3)));
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

} // end namespace dallaswah
