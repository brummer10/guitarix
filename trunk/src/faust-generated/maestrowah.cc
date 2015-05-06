// generated from file '../src/faust/maestrowah.dsp' by dsp2cc:
// Code generated with Faust 0.9.65 (http://faust.grame.fr)


namespace maestrowah {

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
	id = "maestrowah";
	name = N_("Maestro Wah");
	groups = 0;
	description = N_("Maestro Boomerang  Wah  EG-1"); // description (tooltip)
	category = N_("Guitar Effects");       // category
	shortname = N_("Maestro Wah");     // shortname
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
	fConst2 = (1.27725343977795e-29 * fConst1);
	fConst3 = (1.05287431081816e-16 + (fConst1 * (7.49826239560209e-18 + (fConst1 * (8.20619385097054e-20 + (fConst1 * (2.36856089880348e-22 + (fConst1 * (1.87739796916718e-26 + fConst2)))))))));
	fConst4 = (0.10471975511965977 / double(iConst0));
	fConst5 = exp((0 - (1e+01 / double(iConst0))));
	fConst6 = (1.0 - fConst5);
	fConst7 = exp((0 - (1e+02 / double(iConst0))));
	fConst8 = (1.0 - fConst7);
	fConst9 = (1.9610135138181e-31 * fConst1);
	fConst10 = (fConst1 * ((fConst1 * ((fConst1 * ((fConst1 * (0 - (9.896367182867e-28 + fConst9))) - 8.75733379819361e-24)) - 1.80287810387687e-21)) - 8.70288665093646e-21));
	fConst11 = (1.36256412442164e-28 * fConst1);
	fConst12 = (1.74057733018729e-18 + (fConst1 * (3.70846672531016e-19 + (fConst1 * (6.77652355279003e-21 + (fConst1 * (2.56429016897871e-23 + (fConst1 * (3.99675885805637e-26 + fConst11)))))))));
	fConst13 = (1.17540074891101e-30 * fConst1);
	fConst14 = ((fConst1 * (3.84214613809295e-23 + (fConst1 * (fConst13 - 1.07086033539464e-26)))) - 6.72783466104334e-22);
	fConst15 = (1.17272340720388e-30 * fConst1);
	fConst16 = (6.72690759164588e-22 + (fConst1 * ((fConst1 * (1.07070902223171e-26 - fConst15)) - 3.8421155075404e-23)));
	fConst17 = (1.51773160849695e-29 * fConst1);
	fConst18 = ((fConst1 * (2.19849670514246e-20 + (fConst1 * ((fConst1 * (1.7768404223597e-25 - fConst17)) - 7.65801073152836e-22)))) - 1.50703496407371e-19);
	fConst19 = ((fConst1 * (7.49826239560209e-18 + (fConst1 * ((fConst1 * (2.36856089880348e-22 + (fConst1 * (fConst2 - 1.87739796916718e-26)))) - 8.20619385097054e-20)))) - 1.05287431081816e-16);
	fConst20 = (fConst1 * ((fConst1 * (1.80287810387687e-21 + (fConst1 * ((fConst1 * (9.896367182867e-28 - fConst9)) - 8.75733379819361e-24)))) - 8.70288665093646e-21));
	fConst21 = ((fConst1 * (3.70846672531016e-19 + (fConst1 * ((fConst1 * (2.56429016897871e-23 + (fConst1 * (fConst11 - 3.99675885805637e-26)))) - 6.77652355279003e-21)))) - 1.74057733018729e-18);
	fConst22 = (7.66352063866769e-29 * fConst1);
	fConst23 = faustpower<2>(fConst1);
	fConst24 = ((fConst1 * (1.49965247912042e-17 + (fConst23 * ((fConst1 * (7.5095918766687e-26 - fConst22)) - 4.73712179760696e-22)))) - 4.21149724327264e-16);
	fConst25 = (1.17660810829086e-30 * fConst1);
	fConst26 = (fConst1 * ((fConst23 * (1.75146675963872e-23 + (fConst1 * (fConst25 - 3.9585468731468e-27)))) - 1.74057733018729e-20));
	fConst27 = (8.17538474652987e-28 * fConst1);
	fConst28 = ((fConst1 * (7.41693345062033e-19 + (fConst23 * ((fConst1 * (1.59870354322255e-25 - fConst27)) - 5.12858033795743e-23)))) - 6.96230932074917e-18);
	fConst29 = (1.91588015966692e-28 * fConst1);
	fConst30 = ((fConst1 * ((fConst1 * (2.46185815529116e-19 + (fConst1 * ((fConst1 * (fConst29 - 9.38698984583588e-26)) - 2.36856089880348e-22)))) - 7.49826239560209e-18)) - 5.2643715540908e-16);
	fConst31 = (2.94152027072716e-30 * fConst1);
	fConst32 = (fConst1 * (8.70288665093646e-21 + (fConst1 * ((fConst1 * (8.75733379819361e-24 + (fConst1 * (4.9481835914335e-27 - fConst31)))) - 5.40863431163062e-21))));
	fConst33 = (2.04384618663247e-27 * fConst1);
	fConst34 = ((fConst1 * ((fConst1 * (2.03295706583701e-20 + (fConst1 * ((fConst1 * (fConst33 - 1.99837942902818e-25)) - 2.56429016897871e-23)))) - 3.70846672531016e-19)) - 8.70288665093646e-18);
	fConst35 = ((fConst23 * (9.47424359521391e-22 - (2.5545068795559e-28 * fConst23))) - 2.99930495824084e-17);
	fConst36 = (3.48115466037458e-20 + (fConst23 * ((3.92202702763621e-30 * fConst23) - 3.50293351927744e-23)));
	fConst37 = ((fConst23 * (1.02571606759149e-22 - (2.72512824884329e-27 * fConst23))) - 1.48338669012407e-18);
	fConst38 = (5.2643715540908e-16 + (fConst1 * ((fConst1 * ((fConst1 * ((fConst1 * (9.38698984583588e-26 + fConst29)) - 2.36856089880348e-22)) - 2.46185815529116e-19)) - 7.49826239560209e-18)));
	fConst39 = (fConst1 * (8.70288665093646e-21 + (fConst1 * (5.40863431163062e-21 + (fConst1 * (8.75733379819361e-24 + (fConst1 * (0 - (4.9481835914335e-27 + fConst31)))))))));
	fConst40 = (8.70288665093646e-18 + (fConst1 * ((fConst1 * ((fConst1 * ((fConst1 * (1.99837942902818e-25 + fConst33)) - 2.56429016897871e-23)) - 2.03295706583701e-20)) - 3.70846672531016e-19)));
	fConst41 = (4.21149724327264e-16 + (fConst1 * (1.49965247912042e-17 + (fConst23 * ((fConst1 * (0 - (7.5095918766687e-26 + fConst22))) - 4.73712179760696e-22)))));
	fConst42 = (fConst1 * ((fConst23 * (1.75146675963872e-23 + (fConst1 * (3.9585468731468e-27 + fConst25)))) - 1.74057733018729e-20));
	fConst43 = (6.96230932074917e-18 + (fConst1 * (7.41693345062033e-19 + (fConst23 * ((fConst1 * (0 - (1.59870354322255e-25 + fConst27))) - 5.12858033795743e-23)))));
	fConst44 = (7.05240449346608e-30 * fConst1);
	fConst45 = ((fConst1 * (4.28344134157857e-26 - fConst44)) - 7.6842922761859e-23);
	fConst46 = (7.03634044322325e-30 * fConst1);
	fConst47 = (7.68423101508079e-23 + (fConst1 * (fConst46 - 4.28283608892684e-26)));
	fConst48 = (9.10638965098171e-29 * fConst1);
	fConst49 = ((fConst23 * (1.53160214630567e-21 + (fConst1 * (fConst48 - 7.1073616894388e-25)))) - 3.01406992814742e-19);
	fConst50 = (1.76310112336652e-29 * fConst1);
	fConst51 = (2.018350398313e-21 + (fConst1 * ((fConst1 * (fConst50 - 5.35430167697321e-26)) - 3.84214613809295e-23)));
	fConst52 = (1.75908511080581e-29 * fConst1);
	fConst53 = ((fConst1 * (3.8421155075404e-23 + (fConst1 * (5.35354511115855e-26 - fConst52)))) - 2.01807227749376e-21);
	fConst54 = (2.27659741274543e-28 * fConst1);
	fConst55 = (1.50703496407371e-19 + (fConst1 * ((fConst1 * (7.65801073152836e-22 + (fConst1 * (8.8842021117985e-25 - fConst54)))) - 6.59549011542738e-20)));
	fConst56 = (1.53685845523718e-22 - (2.35080149782203e-29 * fConst23));
	fConst57 = ((2.34544681440775e-29 * fConst23) - 1.53684620301616e-22);
	fConst58 = (6.02813985629483e-19 + (fConst23 * ((3.0354632169939e-28 * fConst23) - 3.06320429261135e-21)));
	fConst59 = ((fConst1 * ((fConst1 * (5.35430167697321e-26 + fConst50)) - 3.84214613809295e-23)) - 2.018350398313e-21);
	fConst60 = (2.01807227749376e-21 + (fConst1 * (3.8421155075404e-23 + (fConst1 * (0 - (5.35354511115855e-26 + fConst52))))));
	fConst61 = (1.50703496407371e-19 + (fConst1 * (6.59549011542738e-20 + (fConst1 * (7.65801073152836e-22 + (fConst1 * (0 - (8.8842021117985e-25 + fConst54))))))));
	fConst62 = ((fConst1 * (0 - (4.28344134157857e-26 + fConst44))) - 7.6842922761859e-23);
	fConst63 = (7.68423101508079e-23 + (fConst1 * (4.28283608892684e-26 + fConst46)));
	fConst64 = ((fConst23 * (1.53160214630567e-21 + (fConst1 * (7.1073616894388e-25 + fConst48)))) - 3.01406992814742e-19);
	fConst65 = (6.72783466104334e-22 + (fConst1 * (3.84214613809295e-23 + (fConst1 * (1.07086033539464e-26 + fConst13)))));
	fConst66 = ((fConst1 * ((fConst1 * (0 - (1.07070902223171e-26 + fConst15))) - 3.8421155075404e-23)) - 6.72690759164588e-22);
	fConst67 = ((fConst1 * ((fConst1 * ((fConst1 * (0 - (1.7768404223597e-25 + fConst17))) - 7.65801073152836e-22)) - 2.19849670514246e-20)) - 1.50703496407371e-19);
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
	double 	fSlow1 = (0.004073836948085289 * (exp((1 - double(fslider1))) - 1));
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
		double fTemp2 = ((iSlow2==0)? fRec5[0] : ((iSlow2==1)?max(0.09, min(0.75, fRec3[0])):(1 - max(0.25, min(0.91, (0.5 * (1 + fRec0[0])))))) );
		double fTemp3 = (3.48115466037458e-16 + (fConst1 * ((fTemp2 * (fConst12 + (fConst10 * fTemp2))) + fConst3)));
		fRec6[0] = ((fSlow3 * fTemp0) - (((((((fRec6[1] * (2.08869279622475e-15 + (fConst1 * ((fTemp2 * (fConst43 + (fConst42 * fTemp2))) + fConst41)))) + (fRec6[2] * (5.22173199056188e-15 + (fConst1 * ((fTemp2 * (fConst40 + (fConst39 * fTemp2))) + fConst38))))) + (fRec6[3] * (6.96230932074917e-15 + (fConst23 * ((fTemp2 * (fConst37 + (fConst36 * fTemp2))) + fConst35))))) + (fRec6[4] * (5.22173199056188e-15 + (fConst1 * ((fTemp2 * (fConst34 + (fConst32 * fTemp2))) + fConst30))))) + (fRec6[5] * (2.08869279622475e-15 + (fConst1 * ((fTemp2 * (fConst28 + (fConst26 * fTemp2))) + fConst24))))) + (fRec6[6] * (3.48115466037458e-16 + (fConst1 * ((fTemp2 * (fConst21 + (fConst20 * fTemp2))) + fConst19))))) / fTemp3));
		output0[i] = (FAUSTFLOAT)((fSlow4 * fTemp0) + (fConst23 * ((((((((fRec6[0] * (fConst67 + (fConst1 * (fTemp2 * (fConst66 + (fConst65 * fTemp2)))))) + (fRec6[1] * (fConst64 + (fConst23 * (fTemp2 * (fConst63 + (fConst62 * fTemp2))))))) + (fRec6[2] * (fConst61 + (fConst1 * (fTemp2 * (fConst60 + (fConst59 * fTemp2))))))) + (fRec6[3] * (fConst58 + (fConst23 * (fTemp2 * (fConst57 + (fConst56 * fTemp2))))))) + (fRec6[4] * (fConst55 + (fConst1 * (fTemp2 * (fConst53 + (fConst51 * fTemp2))))))) + (fRec6[5] * (fConst49 + (fConst23 * (fTemp2 * (fConst47 + (fConst45 * fTemp2))))))) + (fRec6[6] * (fConst18 + (fConst1 * (fTemp2 * (fConst16 + (fConst14 * fTemp2))))))) / fTemp3)));
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

} // end namespace maestrowah
