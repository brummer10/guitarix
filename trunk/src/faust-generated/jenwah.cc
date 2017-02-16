// generated from file '../src/faust/jenwah.dsp' by dsp2cc:
// Code generated with Faust 0.9.73 (http://faust.grame.fr)


namespace jenwah {

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
	id = "jenwah";
	name = N_("Jen Wah");
	groups = 0;
	description = N_("Jen Wah"); // description (tooltip)
	category = N_("Guitar Effects");       // category
	shortname = N_("Jen Wah");     // shortname
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
	fConst2 = (1.18553561246751e-20 * fConst1);
	fConst3 = (1.0981649358109e-11 + (fConst1 * (5.79248390117011e-13 + (fConst1 * (3.2569797714609e-17 + fConst2)))));
	fConst4 = (0.10471975511965977 / double(iConst0));
	fConst5 = exp((0 - (1e+01 / double(iConst0))));
	fConst6 = (1.0 - fConst5);
	fConst7 = exp((0 - (1e+02 / double(iConst0))));
	fConst8 = (1.0 - fConst7);
	fConst9 = (6.99671191908366e-20 * fConst1);
	fConst10 = (fConst1 * ((fConst1 * (0 - (1.39394278118629e-17 + fConst9))) - 1.21159485597039e-13));
	fConst11 = (3.85720103312511e-19 * fConst1);
	fConst12 = (2.75362467265997e-12 + (fConst1 * (1.05494945988648e-13 + (fConst1 * (2.77707619975565e-17 + fConst11)))));
	fConst13 = (7.44753937081794e-21 * fConst1);
	fConst14 = (2.09356017382726e-14 + (fConst1 * ((fConst1 * (2.45894566379345e-16 - fConst13)) - 3.53469573143013e-13)));
	fConst15 = (4.26313918949843e-21 * fConst1);
	fConst16 = (fConst1 * (9.21166476483994e-14 + (fConst1 * (fConst15 - 6.7438235280676e-17))));
	fConst17 = (4.24968880185418e-21 * fConst1);
	fConst18 = (1.7091597982174e-12 + (fConst1 * ((fConst1 * (6.74722090896416e-17 - fConst17)) - 9.33056295237144e-14)));
	fConst19 = ((fConst1 * (5.79248390117011e-13 + (fConst1 * (fConst2 - 3.2569797714609e-17)))) - 1.0981649358109e-11);
	fConst20 = (fConst1 * ((fConst1 * (1.39394278118629e-17 - fConst9)) - 1.21159485597039e-13));
	fConst21 = ((fConst1 * (1.05494945988648e-13 + (fConst1 * (fConst11 - 2.77707619975565e-17)))) - 2.75362467265997e-12);
	fConst22 = (4.74214244987003e-20 * fConst1);
	fConst23 = faustpower<2>(fConst1);
	fConst24 = ((fConst23 * (6.51395954292179e-17 - fConst22)) - 2.19632987162179e-11);
	fConst25 = (2.79868476763347e-19 * fConst1);
	fConst26 = (fConst23 * (fConst25 - 2.78788556237258e-17));
	fConst27 = (1.54288041325004e-18 * fConst1);
	fConst28 = ((fConst23 * (5.55415239951129e-17 - fConst27)) - 5.50724934531995e-12);
	fConst29 = (2.42318971194078e-13 - (4.1980271514502e-19 * fConst23));
	fConst30 = ((2.31432061987506e-18 * fConst23) - 2.10989891977295e-13);
	fConst31 = ((7.11321367480505e-20 * fConst23) - 1.15849678023402e-12);
	fConst32 = (2.19632987162179e-11 + (fConst23 * (0 - (6.51395954292179e-17 + fConst22))));
	fConst33 = (fConst23 * (2.78788556237258e-17 + fConst25));
	fConst34 = (5.50724934531995e-12 + (fConst23 * (0 - (5.55415239951129e-17 + fConst27))));
	fConst35 = (716.9748491638952 / double(iConst0));
	fConst36 = (1 + fConst35);
	fConst37 = (0.01 / fConst36);
	fConst38 = (1 - fConst35);
	fConst39 = (1.0 / fConst36);
	fConst40 = (2.97901574832717e-20 * fConst1);
	fConst41 = (4.18712034765452e-14 + (fConst23 * (fConst40 - 4.9178913275869e-16)));
	fConst42 = (1.70525567579937e-20 * fConst1);
	fConst43 = (fConst23 * (1.34876470561352e-16 - fConst42));
	fConst44 = (1.69987552074167e-20 * fConst1);
	fConst45 = (3.41831959643481e-12 + (fConst23 * (fConst44 - 1.34944418179283e-16)));
	fConst46 = (7.06939146286026e-13 - (4.46852362249076e-20 * fConst23));
	fConst47 = ((2.55788351369906e-20 * fConst23) - 1.84233295296799e-13);
	fConst48 = (1.86611259047429e-13 - (2.54981328111251e-20 * fConst23));
	fConst49 = ((fConst23 * (4.9178913275869e-16 + fConst40)) - 4.18712034765452e-14);
	fConst50 = (fConst23 * (0 - (1.34876470561352e-16 + fConst42)));
	fConst51 = ((fConst23 * (1.34944418179283e-16 + fConst44)) - 3.41831959643481e-12);
	fConst52 = ((fConst1 * ((fConst1 * (0 - (2.45894566379345e-16 + fConst13))) - 3.53469573143013e-13)) - 2.09356017382726e-14);
	fConst53 = (fConst1 * (9.21166476483994e-14 + (fConst1 * (6.7438235280676e-17 + fConst15))));
	fConst54 = ((fConst1 * ((fConst1 * (0 - (6.74722090896416e-17 + fConst17))) - 9.33056295237144e-14)) - 1.7091597982174e-12);
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
	double 	fSlow1 = (4.748558434412966e-05 * (exp((5 * (1 - double(fslider1)))) - 1));
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
		fRec5[0] = max(fTemp1, ((fConst5 * fRec5[1]) + (fConst6 * fTemp1)));
		fRec4[0] = ((fConst7 * fRec4[1]) + (fConst8 * fRec5[0]));
		fRec3[0] = ((0.993 * fRec3[1]) + (0.007000000000000006 * max(0.1, min(0.99, fRec4[0]))));
		fRec6[0] = ((0.993 * fRec6[1]) + fSlow1);
		double fTemp2 = ((iSlow2==0)? fRec6[0] : ((iSlow2==1)?fRec3[0]:(1 - max(0.01, min(0.98, (0.5 * (1 + fRec0[0])))))) );
		double fTemp3 = (6.25823789240903e-13 + (fConst1 * ((fTemp2 * (fConst12 + (fConst10 * fTemp2))) + fConst3)));
		fVec1[0] = (fSlow4 * fTemp0);
		fRec8[0] = ((fConst39 * ((fSlow5 * fTemp0) + (fConst38 * fRec8[1]))) - fVec1[1]);
		fRec7[0] = (fRec8[0] - (((((fRec7[1] * (2.50329515696361e-12 + (fConst1 * ((fTemp2 * (fConst34 + (fConst33 * fTemp2))) + fConst32)))) + (fRec7[2] * (3.75494273544542e-12 + (fConst23 * (fConst31 + (fTemp2 * (fConst30 + (fConst29 * fTemp2)))))))) + (fRec7[3] * (2.50329515696361e-12 + (fConst1 * ((fTemp2 * (fConst28 + (fConst26 * fTemp2))) + fConst24))))) + (fRec7[4] * (6.25823789240903e-13 + (fConst1 * ((fTemp2 * (fConst21 + (fConst20 * fTemp2))) + fConst19))))) / fTemp3));
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

} // end namespace jenwah
