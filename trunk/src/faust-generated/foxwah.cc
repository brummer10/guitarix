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
	double 	fConst44;
	double 	fConst45;
	double 	fConst46;
	double 	fVec1[2];
	double 	fConst47;
	double 	fConst48;
	double 	fRec8[2];
	double 	fRec7[7];
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
	double 	fConst68;
	double 	fConst69;
	double 	fConst70;
	double 	fConst71;
	double 	fConst72;
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
	for (int i=0; i<7; i++) fRec7[i] = 0;
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
	fConst2 = (1.31056486224973e-28 * fConst1);
	fConst3 = (5.08453859893818e-17 + (fConst1 * (4.15002440003883e-18 + (fConst1 * (1.10375552149592e-19 + (fConst1 * (1.55788981956485e-22 + (fConst1 * (1.12725575942016e-25 + fConst2)))))))));
	fConst4 = (0.10471975511965977 / double(iConst0));
	fConst5 = exp((0 - (1e+01 / double(iConst0))));
	fConst6 = (1.0 - fConst5);
	fConst7 = exp((0 - (1e+02 / double(iConst0))));
	fConst8 = (1.0 - fConst7);
	fConst9 = (2.25449892184273e-29 * fConst1);
	fConst10 = (fConst1 * ((fConst1 * ((fConst1 * ((fConst1 * (0 - (1.9277250101687e-26 + fConst9))) - 2.4070506850132e-23)) - 1.64046518630872e-20)) - 2.23174133838697e-19));
	fConst11 = (9.046232655478e-29 * fConst1);
	fConst12 = ((fConst1 * ((fConst1 * (1.1492280506911e-20 + (fConst1 * (1.2582355015771e-23 + (fConst1 * (0 - (7.13923782889043e-26 + fConst11))))))) - 1.61228897189633e-19)) - 5.63571045047215e-18);
	fConst13 = (3.01712837658666e-30 * fConst1);
	fConst14 = ((fConst1 * (1.18270878471141e-20 + (fConst1 * ((fConst1 * (1.00001164741986e-25 - fConst13)) - 1.50552858206142e-22)))) - 1.03261821057402e-19);
	fConst15 = (7.82331059004192e-31 * fConst1);
	fConst16 = (fConst1 * ((fConst1 * (2.75196531908426e-23 + (fConst1 * (fConst15 - 1.87212425726617e-26)))) - 1.89966352721393e-21));
	fConst17 = (8.70084394409575e-31 * fConst1);
	fConst18 = (4.49643377593909e-20 + (fConst1 * (1.4599239758417e-21 + (fConst1 * ((fConst1 * (2.07883929004669e-26 - fConst17)) - 3.01424368528688e-23)))));
	fConst19 = ((fConst1 * (4.15002440003883e-18 + (fConst1 * ((fConst1 * (1.55788981956485e-22 + (fConst1 * (fConst2 - 1.12725575942016e-25)))) - 1.10375552149592e-19)))) - 5.08453859893818e-17);
	fConst20 = (fConst1 * ((fConst1 * (1.64046518630872e-20 + (fConst1 * ((fConst1 * (1.9277250101687e-26 - fConst9)) - 2.4070506850132e-23)))) - 2.23174133838697e-19));
	fConst21 = (5.63571045047215e-18 + (fConst1 * ((fConst1 * ((fConst1 * (1.2582355015771e-23 + (fConst1 * (7.13923782889043e-26 - fConst11)))) - 1.1492280506911e-20)) - 1.61228897189633e-19)));
	fConst22 = (7.86338917349835e-28 * fConst1);
	fConst23 = faustpower<2>(fConst1);
	fConst24 = ((fConst1 * (8.30004880007766e-18 + (fConst23 * ((fConst1 * (4.50902303768066e-25 - fConst22)) - 3.11577963912971e-22)))) - 2.03381543957527e-16);
	fConst25 = (1.35269935310564e-28 * fConst1);
	fConst26 = (fConst1 * ((fConst23 * (4.81410137002639e-23 + (fConst1 * (fConst25 - 7.71090004067479e-26)))) - 4.46348267677394e-19));
	fConst27 = (5.4277395932868e-28 * fConst1);
	fConst28 = (2.25428418018886e-17 + (fConst1 * ((fConst23 * ((fConst1 * (fConst27 - 2.85569513155617e-25)) - 2.5164710031542e-23)) - 3.22457794379266e-19)));
	fConst29 = (1.96584729337459e-27 * fConst1);
	fConst30 = ((fConst1 * ((fConst1 * (3.31126656448775e-19 + (fConst1 * ((fConst1 * (fConst29 - 5.63627879710083e-25)) - 1.55788981956485e-22)))) - 4.15002440003883e-18)) - 2.54226929946909e-16);
	fConst31 = (3.3817483827641e-28 * fConst1);
	fConst32 = (fConst1 * (2.23174133838697e-19 + (fConst1 * ((fConst1 * (2.4070506850132e-23 + (fConst1 * (9.63862505084349e-26 - fConst31)))) - 4.92139555892616e-20))));
	fConst33 = (1.3569348983217e-27 * fConst1);
	fConst34 = (2.81785522523607e-17 + (fConst1 * (1.61228897189633e-19 + (fConst1 * (3.44768415207329e-20 + (fConst1 * ((fConst1 * (3.56961891444522e-25 - fConst33)) - 1.2582355015771e-23)))))));
	fConst35 = ((fConst23 * (6.23155927825941e-22 - (2.62112972449945e-27 * fConst23))) - 1.66000976001553e-17);
	fConst36 = (8.92696535354788e-19 + (fConst23 * ((4.50899784368546e-28 * fConst23) - 9.62820274005279e-23)));
	fConst37 = (6.44915588758531e-19 + (fConst23 * (5.03294200630841e-23 + (1.8092465310956e-27 * fConst23))));
	fConst38 = (2.54226929946909e-16 + (fConst1 * ((fConst1 * ((fConst1 * ((fConst1 * (5.63627879710083e-25 + fConst29)) - 1.55788981956485e-22)) - 3.31126656448775e-19)) - 4.15002440003883e-18)));
	fConst39 = (fConst1 * (2.23174133838697e-19 + (fConst1 * (4.92139555892616e-20 + (fConst1 * (2.4070506850132e-23 + (fConst1 * (0 - (9.63862505084349e-26 + fConst31)))))))));
	fConst40 = ((fConst1 * (1.61228897189633e-19 + (fConst1 * ((fConst1 * ((fConst1 * (0 - (3.56961891444522e-25 + fConst33))) - 1.2582355015771e-23)) - 3.44768415207329e-20)))) - 2.81785522523607e-17);
	fConst41 = (2.03381543957527e-16 + (fConst1 * (8.30004880007766e-18 + (fConst23 * ((fConst1 * (0 - (4.50902303768066e-25 + fConst22))) - 3.11577963912971e-22)))));
	fConst42 = (fConst1 * ((fConst23 * (4.81410137002639e-23 + (fConst1 * (7.71090004067479e-26 + fConst25)))) - 4.46348267677394e-19));
	fConst43 = ((fConst1 * ((fConst23 * ((fConst1 * (2.85569513155617e-25 + fConst27)) - 2.5164710031542e-23)) - 3.22457794379266e-19)) - 2.25428418018886e-17);
	fConst44 = (716.6140154481191 / double(iConst0));
	fConst45 = (1 + fConst44);
	fConst46 = (0.01 / fConst45);
	fConst47 = (1 - fConst44);
	fConst48 = (1.0 / fConst45);
	fConst49 = (1.81027702595199e-29 * fConst1);
	fConst50 = ((fConst23 * (3.01105716412283e-22 + (fConst1 * (fConst49 - 4.00004658967943e-25)))) - 2.06523642114804e-19);
	fConst51 = (4.69398635402515e-30 * fConst1);
	fConst52 = (fConst23 * ((fConst1 * (7.48849702906466e-26 - fConst51)) - 5.50393063816852e-23));
	fConst53 = (5.22050636645745e-30 * fConst1);
	fConst54 = (8.99286755187819e-20 + (fConst23 * (6.02848737057377e-23 + (fConst1 * (fConst53 - 8.31535716018674e-26)))));
	fConst55 = (4.52569256487998e-29 * fConst1);
	fConst56 = (1.03261821057402e-19 + (fConst1 * ((fConst1 * (1.50552858206142e-22 + (fConst1 * (5.00005823709929e-25 - fConst55)))) - 3.54812635413424e-20)));
	fConst57 = (1.17349658850629e-29 * fConst1);
	fConst58 = (fConst1 * (5.69899058164178e-21 + (fConst1 * ((fConst1 * (fConst57 - 9.36062128633083e-26)) - 2.75196531908426e-23))));
	fConst59 = (1.30512659161436e-29 * fConst1);
	fConst60 = ((fConst1 * ((fConst1 * (3.01424368528688e-23 + (fConst1 * (1.03941964502334e-25 - fConst59)))) - 4.37977192752511e-21)) - 4.49643377593909e-20);
	fConst61 = (4.13047284229608e-19 + (fConst23 * ((6.03425675317331e-29 * fConst23) - 6.02211432824566e-22)));
	fConst62 = (fConst23 * (1.1007861276337e-22 - (1.56466211800838e-29 * fConst23)));
	fConst63 = ((fConst23 * ((1.74016878881915e-29 * fConst23) - 1.20569747411475e-22)) - 1.79857351037564e-19);
	fConst64 = (1.03261821057402e-19 + (fConst1 * (3.54812635413424e-20 + (fConst1 * (1.50552858206142e-22 + (fConst1 * (0 - (5.00005823709929e-25 + fConst55))))))));
	fConst65 = (fConst1 * ((fConst1 * ((fConst1 * (9.36062128633083e-26 + fConst57)) - 2.75196531908426e-23)) - 5.69899058164178e-21));
	fConst66 = ((fConst1 * (4.37977192752511e-21 + (fConst1 * (3.01424368528688e-23 + (fConst1 * (0 - (1.03941964502334e-25 + fConst59))))))) - 4.49643377593909e-20);
	fConst67 = ((fConst23 * (3.01105716412283e-22 + (fConst1 * (4.00004658967943e-25 + fConst49)))) - 2.06523642114804e-19);
	fConst68 = (fConst23 * ((fConst1 * (0 - (7.48849702906466e-26 + fConst51))) - 5.50393063816852e-23));
	fConst69 = (8.99286755187819e-20 + (fConst23 * (6.02848737057377e-23 + (fConst1 * (8.31535716018674e-26 + fConst53)))));
	fConst70 = ((fConst1 * ((fConst1 * ((fConst1 * (0 - (1.00001164741986e-25 + fConst13))) - 1.50552858206142e-22)) - 1.18270878471141e-20)) - 1.03261821057402e-19);
	fConst71 = (fConst1 * (1.89966352721393e-21 + (fConst1 * (2.75196531908426e-23 + (fConst1 * (1.87212425726617e-26 + fConst15))))));
	fConst72 = (4.49643377593909e-20 + (fConst1 * ((fConst1 * ((fConst1 * (0 - (2.07883929004669e-26 + fConst17))) - 3.01424368528688e-23)) - 1.4599239758417e-21)));
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
	double 	fSlow1 = (0.004073836948085289 * (exp(max(0.01, double(fslider1))) - 1));
	int 	iSlow2 = int(double(fslider2));
	double 	fSlow3 = double(fslider3);
	double 	fSlow4 = (fConst46 * fSlow3);
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
		double fTemp3 = (1.42315920466468e-16 + (fConst1 * ((fTemp2 * (fConst12 + (fConst10 * fTemp2))) + fConst3)));
		fVec1[0] = (fSlow4 * fTemp0);
		fRec8[0] = ((fConst48 * ((fSlow5 * fTemp0) + (fConst47 * fRec8[1]))) - fVec1[1]);
		fRec7[0] = (fRec8[0] - (((((((fRec7[1] * (8.5389552279881e-16 + (fConst1 * ((fTemp2 * (fConst43 + (fConst42 * fTemp2))) + fConst41)))) + (fRec7[2] * (2.13473880699702e-15 + (fConst1 * ((fTemp2 * (fConst40 + (fConst39 * fTemp2))) + fConst38))))) + (fRec7[3] * (2.84631840932937e-15 + (fConst23 * ((fTemp2 * (fConst37 + (fConst36 * fTemp2))) + fConst35))))) + (fRec7[4] * (2.13473880699702e-15 + (fConst1 * ((fTemp2 * (fConst34 + (fConst32 * fTemp2))) + fConst30))))) + (fRec7[5] * (8.5389552279881e-16 + (fConst1 * ((fTemp2 * (fConst28 + (fConst26 * fTemp2))) + fConst24))))) + (fRec7[6] * (1.42315920466468e-16 + (fConst1 * ((fTemp2 * (fConst21 + (fConst20 * fTemp2))) + fConst19))))) / fTemp3));
		output0[i] = (FAUSTFLOAT)((fSlow6 * fTemp0) + (fConst23 * ((((((((fRec7[0] * ((fTemp2 * (fConst72 + (fConst71 * fTemp2))) + fConst70)) + (fRec7[1] * ((fTemp2 * (fConst69 + (fConst68 * fTemp2))) + fConst67))) + (fRec7[2] * ((fTemp2 * (fConst66 + (fConst65 * fTemp2))) + fConst64))) + (fRec7[3] * ((fTemp2 * (fConst63 + (fConst62 * fTemp2))) + fConst61))) + (fRec7[4] * ((fTemp2 * (fConst60 + (fConst58 * fTemp2))) + fConst56))) + (fRec7[5] * ((fTemp2 * (fConst54 + (fConst52 * fTemp2))) + fConst50))) + (fRec7[6] * ((fTemp2 * (fConst18 + (fConst16 * fTemp2))) + fConst14))) / fTemp3)));
		// post processing
		for (int i=6; i>0; i--) fRec7[i] = fRec7[i-1];
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
