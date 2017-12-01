// generated from file '../src/faust/jenbasswah.dsp' by dsp2cc:
// Code generated with Faust 0.9.90 (http://faust.grame.fr)


namespace jenbasswah {

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
	fConst7 = (7.02628418882998e-20 * fConst6);
	fConst8 = ((fConst6 * (0 - (8.45822966675918e-18 + fConst7))) - 1.78928790753088e-14);
	fConst9 = (3.87350386089898e-19 * fConst6);
	fConst10 = (1.57249804702232e-14 + (fConst6 * (2.30787830877444e-17 + fConst9)));
	fConst11 = (1.19054639174528e-20 * fConst6);
	fConst12 = (1.62180722455991e-12 + (fConst6 * (8.55689125277824e-14 + (fConst6 * (6.24901706816551e-18 + fConst11)))));
	fConst13 = (4.28115775363339e-21 * fConst6);
	fConst14 = (1.36038216822257e-14 + (fConst6 * (fConst13 - 1.30268272702044e-17)));
	fConst15 = (4.26765051664369e-21 * fConst6);
	fConst16 = ((fConst6 * (1.30609446727126e-17 - fConst15)) - 1.3782974775989e-14);
	fConst17 = (7.47901710601256e-21 * fConst6);
	fConst18 = (3.09177765505129e-15 + (fConst6 * ((fConst6 * (3.70620297844195e-17 - fConst17)) - 5.22012186323421e-14)));
	fConst19 = ((fConst6 * (8.45822966675918e-18 - fConst7)) - 1.78928790753088e-14);
	fConst20 = (1.57249804702232e-14 + (fConst6 * (fConst9 - 2.30787830877444e-17)));
	fConst21 = ((fConst6 * (8.55689125277824e-14 + (fConst6 * (fConst11 - 6.24901706816551e-18)))) - 1.62180722455991e-12);
	fConst22 = (2.81051367553199e-19 * fConst6);
	fConst23 = (fConst22 - 1.69164593335184e-17);
	fConst24 = (1.54940154435959e-18 * fConst6);
	fConst25 = (4.61575661754889e-17 - fConst24);
	fConst26 = faustpower<2>(fConst6);
	fConst27 = (4.76218556698113e-20 * fConst6);
	fConst28 = ((fConst26 * (1.2498034136331e-17 - fConst27)) - 3.24361444911983e-12);
	fConst29 = (1.69164593335184e-17 + fConst22);
	fConst30 = (0 - (4.61575661754889e-17 + fConst24));
	fConst31 = (3.24361444911983e-12 + (fConst26 * (0 - (1.2498034136331e-17 + fConst27))));
	fConst32 = (3.57857581506176e-14 - (4.21577051329799e-19 * fConst26));
	fConst33 = ((2.32410231653939e-18 * fConst26) - 3.14499609404464e-14);
	fConst34 = ((7.1432783504717e-20 * fConst26) - 1.71137825055565e-13);
	fConst35 = (718.2824771643642 / fConst0);
	fConst36 = (1 + fConst35);
	fConst37 = (0.01 / fConst36);
	fConst38 = (1 - fConst35);
	fConst39 = (1.0 / fConst36);
	fConst40 = (1.71246310145335e-20 * fConst6);
	fConst41 = (2.60536545404087e-17 - fConst40);
	fConst42 = (1.70706020665747e-20 * fConst6);
	fConst43 = (fConst42 - 2.61218893454252e-17);
	fConst44 = (2.99160684240502e-20 * fConst6);
	fConst45 = (6.18355531010259e-15 + (fConst26 * (fConst44 - 7.4124059568839e-17)));
	fConst46 = ((2.56869465218003e-20 * fConst26) - 2.72076433644514e-14);
	fConst47 = (2.75659495519781e-14 - (2.56059030998621e-20 * fConst26));
	fConst48 = (1.04402437264684e-13 - (4.48741026360754e-20 * fConst26));
	fConst49 = (0 - (2.60536545404087e-17 + fConst40));
	fConst50 = (2.61218893454252e-17 + fConst42);
	fConst51 = ((fConst26 * (7.4124059568839e-17 + fConst44)) - 6.18355531010259e-15);
	fConst52 = (1.36038216822257e-14 + (fConst6 * (1.30268272702044e-17 + fConst13)));
	fConst53 = ((fConst6 * (0 - (1.30609446727126e-17 + fConst15))) - 1.3782974775989e-14);
	fConst54 = ((fConst6 * ((fConst6 * (0 - (3.70620297844195e-17 + fConst17))) - 5.22012186323421e-14)) - 3.09177765505129e-15);
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
	double 	fSlow1 = (4.748558434412966e-05 * (exp((5 * (1 - double(fslider1)))) - 1));
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
		fRec3[0] = ((0.993 * fRec3[1]) + (0.007000000000000006 * max(0.1, min(0.99, fRec4[0]))));
		fRec6[0] = (fSlow1 + (0.993 * fRec6[1]));
		double fTemp2 = ((iSlow2==0)? fRec6[0] : ((iSlow2==1)?fRec3[0]:(1 - max(0.01, min(0.98, (0.5 * (1 + fRec0[0])))))) );
		double fTemp3 = (9.24218960501488e-14 + (fConst6 * (fConst12 + (fTemp2 * (4.06656342620655e-13 + (fConst6 * (fConst10 + (fConst8 * fTemp2))))))));
		fVec1[0] = (fSlow4 * fTemp0);
		fRec8[0] = ((fConst39 * ((fSlow5 * fTemp0) + (fConst38 * fRec8[1]))) - fVec1[1]);
		fRec7[0] = (fRec8[0] - (((((fRec7[2] * (5.54531376300893e-13 + (fConst26 * (fConst34 + (fTemp2 * (fConst33 + (fConst32 * fTemp2))))))) + (fRec7[1] * (3.69687584200595e-13 + (fConst6 * (fConst31 + (fTemp2 * (8.1331268524131e-13 + (fConst26 * (fConst30 + (fConst29 * fTemp2)))))))))) + (fRec7[3] * (3.69687584200595e-13 + (fConst6 * (fConst28 + (fTemp2 * ((fConst26 * (fConst25 + (fConst23 * fTemp2))) - 8.1331268524131e-13))))))) + (fRec7[4] * (9.24218960501488e-14 + (fConst6 * (fConst21 + (fTemp2 * ((fConst6 * (fConst20 + (fConst19 * fTemp2))) - 4.06656342620655e-13))))))) / fTemp3));
		output0[i] = (FAUSTFLOAT)((fSlow6 * fTemp0) + (fConst6 * ((((((fRec7[0] * (fConst54 + (fTemp2 * ((fConst6 * (fConst53 + (fConst52 * fTemp2))) - 2.52409371323892e-13)))) + (fRec7[1] * (fConst51 + (fTemp2 * ((fConst26 * (fConst50 + (fConst49 * fTemp2))) - 5.04818742647784e-13))))) + (fConst6 * (fRec7[2] * (fConst48 + (fTemp2 * (fConst47 + (fConst46 * fTemp2))))))) + (fRec7[3] * (fConst45 + (fTemp2 * (5.04818742647784e-13 + (fConst26 * (fConst43 + (fConst41 * fTemp2)))))))) + (fRec7[4] * (fConst18 + (fTemp2 * (2.52409371323892e-13 + (fConst6 * (fConst16 + (fConst14 * fTemp2)))))))) / fTemp3)));
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

} // end namespace jenbasswah
