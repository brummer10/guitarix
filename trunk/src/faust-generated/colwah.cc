// generated from file '../src/faust/colwah.dsp' by dsp2cc:
// Code generated with Faust 0.9.65 (http://faust.grame.fr)


namespace colwah {

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
	fConst2 = (2.81322342123736e-30 * fConst1);
	fConst3 = (2.03039414548991e-17 + (fConst1 * (1.31169348705373e-18 + (fConst1 * (2.94448762671775e-20 + (fConst1 * (5.53827044579352e-23 + (fConst1 * (3.61396735526861e-27 + fConst2)))))))));
	fConst4 = (0.10471975511965977 / double(iConst0));
	fConst5 = exp((0 - (1e+01 / double(iConst0))));
	fConst6 = (1.0 - fConst5);
	fConst7 = exp((0 - (1e+02 / double(iConst0))));
	fConst8 = (1.0 - fConst7);
	fConst9 = (2.9944679862091e-29 * fConst1);
	fConst10 = ((fConst1 * ((fConst1 * ((fConst1 * ((fConst1 * (0 - (1.74927096988764e-26 + fConst9))) - 1.25792928205509e-23)) - 5.91446731480775e-21)) - 1.51836846550049e-19)) - 1.031544116964e-18);
	fConst11 = (1.70822585244041e-28 * fConst1);
	fConst12 = (3.10505198843707e-18 + (fConst1 * (2.71483854182133e-19 + (fConst1 * (8.83661131513604e-21 + (fConst1 * (2.25426927212869e-23 + (fConst1 * (9.71341702061507e-26 + fConst11)))))))));
	fConst13 = (1.14655708524549e-30 * fConst1);
	fConst14 = ((fConst1 * (2.12994394902622e-21 + (fConst1 * ((fConst1 * (3.62338673802449e-26 - fConst13)) - 5.6523354018053e-23)))) - 9.55955366951846e-21);
	fConst15 = (3.57054794077438e-31 * fConst1);
	fConst16 = (fConst1 * ((fConst1 * (1.25321322315854e-23 + (fConst1 * (fConst15 - 8.2151955389469e-27)))) - 4.08428676476815e-22));
	fConst17 = (3.53331014667854e-31 * fConst1);
	fConst18 = ((fConst1 * (6.73367038087507e-22 + (fConst1 * ((fConst1 * (8.13766500494647e-27 - fConst17)) - 1.25785612226533e-23)))) - 8.77258904721491e-21);
	fConst19 = ((fConst1 * (1.31169348705373e-18 + (fConst1 * ((fConst1 * (5.53827044579352e-23 + (fConst1 * (fConst2 - 3.61396735526861e-27)))) - 2.94448762671775e-20)))) - 2.03039414548991e-17);
	fConst20 = (1.031544116964e-18 + (fConst1 * ((fConst1 * (5.91446731480775e-21 + (fConst1 * ((fConst1 * (1.74927096988764e-26 - fConst9)) - 1.25792928205509e-23)))) - 1.51836846550049e-19)));
	fConst21 = ((fConst1 * (2.71483854182133e-19 + (fConst1 * ((fConst1 * (2.25426927212869e-23 + (fConst1 * (fConst11 - 9.71341702061507e-26)))) - 8.83661131513604e-21)))) - 3.10505198843707e-18);
	fConst22 = (1.68793405274241e-29 * fConst1);
	fConst23 = faustpower<2>(fConst1);
	fConst24 = ((fConst1 * (2.62338697410746e-18 + (fConst23 * ((fConst1 * (1.44558694210745e-26 - fConst22)) - 1.1076540891587e-22)))) - 8.12157658195965e-17);
	fConst25 = (1.79668079172546e-28 * fConst1);
	fConst26 = (4.126176467856e-18 + (fConst1 * ((fConst23 * (2.51585856411018e-23 + (fConst1 * (fConst25 - 6.99708387955057e-26)))) - 3.03673693100097e-19)));
	fConst27 = (1.02493551146425e-27 * fConst1);
	fConst28 = ((fConst1 * (5.42967708364266e-19 + (fConst23 * ((fConst1 * (3.88536680824603e-25 - fConst27)) - 4.50853854425739e-23)))) - 1.24202079537483e-17);
	fConst29 = (4.21983513185604e-29 * fConst1);
	fConst30 = ((fConst1 * ((fConst1 * (8.83346288015326e-20 + (fConst1 * ((fConst1 * (fConst29 - 1.80698367763431e-26)) - 5.53827044579352e-23)))) - 1.31169348705373e-18)) - 1.01519707274496e-16);
	fConst31 = (4.49170197931365e-28 * fConst1);
	fConst32 = (5.15772058482e-18 + (fConst1 * (1.51836846550049e-19 + (fConst1 * ((fConst1 * (1.25792928205509e-23 + (fConst1 * (8.74635484943821e-26 - fConst31)))) - 1.77434019444233e-20)))));
	fConst33 = (2.56233877866062e-27 * fConst1);
	fConst34 = ((fConst1 * ((fConst1 * (2.65098339454081e-20 + (fConst1 * ((fConst1 * (fConst33 - 4.85670851030753e-25)) - 2.25426927212869e-23)))) - 2.71483854182133e-19)) - 1.55252599421853e-17);
	fConst35 = ((fConst23 * (2.21530817831741e-22 - (5.62644684247472e-29 * fConst23))) - 5.24677394821492e-18);
	fConst36 = (6.07347386200195e-19 + (fConst23 * ((5.9889359724182e-28 * fConst23) - 5.03171712822037e-23)));
	fConst37 = ((fConst23 * (9.01707708851477e-23 - (3.41645170488082e-27 * fConst23))) - 1.08593541672853e-18);
	fConst38 = (1.01519707274496e-16 + (fConst1 * ((fConst1 * ((fConst1 * ((fConst1 * (1.80698367763431e-26 + fConst29)) - 5.53827044579352e-23)) - 8.83346288015326e-20)) - 1.31169348705373e-18)));
	fConst39 = ((fConst1 * (1.51836846550049e-19 + (fConst1 * (1.77434019444233e-20 + (fConst1 * (1.25792928205509e-23 + (fConst1 * (0 - (8.74635484943821e-26 + fConst31))))))))) - 5.15772058482e-18);
	fConst40 = (1.55252599421853e-17 + (fConst1 * ((fConst1 * ((fConst1 * ((fConst1 * (4.85670851030753e-25 + fConst33)) - 2.25426927212869e-23)) - 2.65098339454081e-20)) - 2.71483854182133e-19)));
	fConst41 = (8.12157658195965e-17 + (fConst1 * (2.62338697410746e-18 + (fConst23 * ((fConst1 * (0 - (1.44558694210745e-26 + fConst22))) - 1.1076540891587e-22)))));
	fConst42 = ((fConst1 * ((fConst23 * (2.51585856411018e-23 + (fConst1 * (6.99708387955057e-26 + fConst25)))) - 3.03673693100097e-19)) - 4.126176467856e-18);
	fConst43 = (1.24202079537483e-17 + (fConst1 * (5.42967708364266e-19 + (fConst23 * ((fConst1 * (0 - (3.88536680824603e-25 + fConst27))) - 4.50853854425739e-23)))));
	fConst44 = (6.87934251147295e-30 * fConst1);
	fConst45 = ((fConst23 * (1.13046708036106e-22 + (fConst1 * (fConst44 - 1.4493546952098e-25)))) - 1.91191073390369e-20);
	fConst46 = (2.14232876446463e-30 * fConst1);
	fConst47 = (fConst23 * ((fConst1 * (3.28607821557876e-26 - fConst46)) - 2.50642644631707e-23));
	fConst48 = (2.11998608800713e-30 * fConst1);
	fConst49 = ((fConst23 * (2.51571224453066e-23 + (fConst1 * (fConst48 - 3.25506600197859e-26)))) - 1.75451780944298e-20);
	fConst50 = (1.71983562786824e-29 * fConst1);
	fConst51 = (9.55955366951846e-21 + (fConst1 * ((fConst1 * (5.6523354018053e-23 + (fConst1 * (1.81169336901225e-25 - fConst50)))) - 6.38983184707866e-21)));
	fConst52 = (5.35582191116158e-30 * fConst1);
	fConst53 = (fConst1 * (1.22528602943045e-21 + (fConst1 * ((fConst1 * (fConst52 - 4.10759776947345e-26)) - 1.25321322315854e-23))));
	fConst54 = (5.29996522001782e-30 * fConst1);
	fConst55 = (8.77258904721491e-21 + (fConst1 * ((fConst1 * (1.25785612226533e-23 + (fConst1 * (4.06883250247324e-26 - fConst54)))) - 2.02010111426252e-21)));
	fConst56 = (3.82382146780738e-20 + (fConst23 * ((2.29311417049098e-29 * fConst23) - 2.26093416072212e-22)));
	fConst57 = (fConst23 * (5.01285289263414e-23 - (7.14109588154877e-30 * fConst23)));
	fConst58 = (3.50903561888596e-20 + (fConst23 * ((7.06662029335709e-30 * fConst23) - 5.03142448906131e-23)));
	fConst59 = (9.55955366951846e-21 + (fConst1 * (6.38983184707866e-21 + (fConst1 * (5.6523354018053e-23 + (fConst1 * (0 - (1.81169336901225e-25 + fConst50))))))));
	fConst60 = (fConst1 * ((fConst1 * ((fConst1 * (4.10759776947345e-26 + fConst52)) - 1.25321322315854e-23)) - 1.22528602943045e-21));
	fConst61 = (8.77258904721491e-21 + (fConst1 * (2.02010111426252e-21 + (fConst1 * (1.25785612226533e-23 + (fConst1 * (0 - (4.06883250247324e-26 + fConst54))))))));
	fConst62 = ((fConst23 * (1.13046708036106e-22 + (fConst1 * (1.4493546952098e-25 + fConst44)))) - 1.91191073390369e-20);
	fConst63 = (fConst23 * ((fConst1 * (0 - (3.28607821557876e-26 + fConst46))) - 2.50642644631707e-23));
	fConst64 = ((fConst23 * (2.51571224453066e-23 + (fConst1 * (3.25506600197859e-26 + fConst48)))) - 1.75451780944298e-20);
	fConst65 = ((fConst1 * ((fConst1 * ((fConst1 * (0 - (3.62338673802449e-26 + fConst13))) - 5.6523354018053e-23)) - 2.12994394902622e-21)) - 9.55955366951846e-21);
	fConst66 = (fConst1 * (4.08428676476815e-22 + (fConst1 * (1.25321322315854e-23 + (fConst1 * (8.2151955389469e-27 + fConst15))))));
	fConst67 = ((fConst1 * ((fConst1 * ((fConst1 * (0 - (8.13766500494647e-27 + fConst17))) - 1.25785612226533e-23)) - 6.73367038087507e-22)) - 8.77258904721491e-21);
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
		double fTemp3 = (7.17605891535182e-17 + (fConst1 * ((fTemp2 * (fConst12 + (fConst10 * fTemp2))) + fConst3)));
		fRec6[0] = ((fSlow3 * fTemp0) - (((((((fRec6[1] * (4.30563534921109e-16 + (fConst1 * ((fTemp2 * (fConst43 + (fConst42 * fTemp2))) + fConst41)))) + (fRec6[2] * (1.07640883730277e-15 + (fConst1 * ((fTemp2 * (fConst40 + (fConst39 * fTemp2))) + fConst38))))) + (fRec6[3] * (1.43521178307036e-15 + (fConst23 * ((fTemp2 * (fConst37 + (fConst36 * fTemp2))) + fConst35))))) + (fRec6[4] * (1.07640883730277e-15 + (fConst1 * ((fTemp2 * (fConst34 + (fConst32 * fTemp2))) + fConst30))))) + (fRec6[5] * (4.30563534921109e-16 + (fConst1 * ((fTemp2 * (fConst28 + (fConst26 * fTemp2))) + fConst24))))) + (fRec6[6] * (7.17605891535182e-17 + (fConst1 * ((fTemp2 * (fConst21 + (fConst20 * fTemp2))) + fConst19))))) / fTemp3));
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

} // end namespace colwah
