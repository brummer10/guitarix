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
	double 	fVec1[2];
	double 	fRec7[2];
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
	fConst2 = (2.81471278631794e-30 * fConst1);
	fConst3 = (3.49321549484182e-18 + (fConst1 * (2.10368870184462e-19 + (fConst1 * (4.45731355498812e-21 + (fConst1 * (8.76020695770787e-24 + (fConst1 * (2.58008433630295e-27 + fConst2)))))))));
	fConst4 = (0.10471975511965977 / double(iConst0));
	fConst5 = exp((0 - (1e+01 / double(iConst0))));
	fConst6 = (1.0 - fConst5);
	fConst7 = exp((0 - (1e+02 / double(iConst0))));
	fConst8 = (1.0 - fConst7);
	fConst9 = (2.99605330502527e-29 * fConst1);
	fConst10 = ((fConst1 * ((fConst1 * ((fConst1 * ((fConst1 * (0 - (1.73141762485697e-26 + fConst9))) - 4.13170439634509e-24)) - 1.53438894633014e-21)) - 2.96109822935368e-20)) - 1.51777975407542e-19);
	fConst11 = (1.7091302142831e-28 * fConst1);
	fConst12 = (4.56867037085326e-19 + (fConst1 * (6.18293080646267e-20 + (fConst1 * (5.01959590405437e-21 + (fConst1 * (1.55928165911418e-23 + (fConst1 * (9.70310455902874e-26 + fConst11)))))))));
	fConst13 = (1.14716409074831e-30 * fConst1);
	fConst14 = ((fConst1 * (3.13750854883691e-22 + (fConst1 * ((fConst1 * (5.48068554114285e-27 - fConst13)) - 8.36956063273783e-24)))) - 1.40656097775947e-21);
	fConst15 = (3.57243824546669e-31 * fConst1);
	fConst16 = (fConst1 * ((fConst1 * (1.85927205363659e-24 + (fConst1 * (fConst15 - 1.37637472602693e-27)))) - 6.0094838984169e-23));
	fConst17 = (3.53518073709224e-31 * fConst1);
	fConst18 = ((fConst1 * (9.93106205417573e-23 + (fConst1 * ((fConst1 * (1.36792607610923e-27 - fConst17)) - 1.86661570683084e-24)))) - 1.29076961689941e-21);
	fConst19 = ((fConst1 * (2.10368870184462e-19 + (fConst1 * ((fConst1 * (8.76020695770787e-24 + (fConst1 * (fConst2 - 2.58008433630295e-27)))) - 4.45731355498812e-21)))) - 3.49321549484182e-18);
	fConst20 = (1.51777975407542e-19 + (fConst1 * ((fConst1 * (1.53438894633014e-21 + (fConst1 * ((fConst1 * (1.73141762485697e-26 - fConst9)) - 4.13170439634509e-24)))) - 2.96109822935368e-20)));
	fConst21 = ((fConst1 * (6.18293080646267e-20 + (fConst1 * ((fConst1 * (1.55928165911418e-23 + (fConst1 * (fConst11 - 9.70310455902874e-26)))) - 5.01959590405437e-21)))) - 4.56867037085326e-19);
	fConst22 = (1.68882767179076e-29 * fConst1);
	fConst23 = faustpower<2>(fConst1);
	fConst24 = ((fConst1 * (4.20737740368924e-19 + (fConst23 * ((fConst1 * (1.03203373452118e-26 - fConst22)) - 1.75204139154157e-23)))) - 1.39728619793673e-17);
	fConst25 = (1.79763198301516e-28 * fConst1);
	fConst26 = (6.07111901630169e-19 + (fConst1 * ((fConst23 * (8.26340879269018e-24 + (fConst1 * (fConst25 - 6.92567049942789e-26)))) - 5.92219645870735e-20)));
	fConst27 = (1.02547812856986e-27 * fConst1);
	fConst28 = ((fConst1 * (1.23658616129253e-19 + (fConst23 * ((fConst1 * (3.8812418236115e-25 - fConst27)) - 3.11856331822835e-23)))) - 1.8274681483413e-18);
	fConst29 = (4.22206917947691e-29 * fConst1);
	fConst30 = ((fConst1 * ((fConst1 * (1.33719406649643e-20 + (fConst1 * ((fConst1 * (fConst29 - 1.29004216815147e-26)) - 8.76020695770787e-24)))) - 2.10368870184462e-19)) - 1.74660774742091e-17);
	fConst31 = (4.4940799575379e-28 * fConst1);
	fConst32 = (7.58889877037711e-19 + (fConst1 * (2.96109822935368e-20 + (fConst1 * ((fConst1 * (4.13170439634509e-24 + (fConst1 * (8.65708812428486e-26 - fConst31)))) - 4.60316683899041e-21)))));
	fConst33 = (2.56369532142465e-27 * fConst1);
	fConst34 = ((fConst1 * ((fConst1 * (1.50587877121631e-20 + (fConst1 * ((fConst1 * (fConst33 - 4.85155227951437e-25)) - 1.55928165911418e-23)))) - 6.18293080646267e-20)) - 2.28433518542663e-18);
	fConst35 = ((fConst23 * (3.50408278308315e-23 - (5.62942557263588e-29 * fConst23))) - 8.41475480737849e-19);
	fConst36 = (1.18443929174147e-19 + (fConst23 * ((5.99210661005054e-28 * fConst23) - 1.65268175853804e-23)));
	fConst37 = ((fConst23 * (6.23712663645671e-23 - (3.4182604285662e-27 * fConst23))) - 2.47317232258507e-19);
	fConst38 = (1.74660774742091e-17 + (fConst1 * ((fConst1 * ((fConst1 * ((fConst1 * (1.29004216815147e-26 + fConst29)) - 8.76020695770787e-24)) - 1.33719406649643e-20)) - 2.10368870184462e-19)));
	fConst39 = ((fConst1 * (2.96109822935368e-20 + (fConst1 * (4.60316683899041e-21 + (fConst1 * (4.13170439634509e-24 + (fConst1 * (0 - (8.65708812428486e-26 + fConst31))))))))) - 7.58889877037711e-19);
	fConst40 = (2.28433518542663e-18 + (fConst1 * ((fConst1 * ((fConst1 * ((fConst1 * (4.85155227951437e-25 + fConst33)) - 1.55928165911418e-23)) - 1.50587877121631e-20)) - 6.18293080646267e-20)));
	fConst41 = (1.39728619793673e-17 + (fConst1 * (4.20737740368924e-19 + (fConst23 * ((fConst1 * (0 - (1.03203373452118e-26 + fConst22))) - 1.75204139154157e-23)))));
	fConst42 = ((fConst1 * ((fConst23 * (8.26340879269018e-24 + (fConst1 * (6.92567049942789e-26 + fConst25)))) - 5.92219645870735e-20)) - 6.07111901630169e-19);
	fConst43 = (1.8274681483413e-18 + (fConst1 * (1.23658616129253e-19 + (fConst23 * ((fConst1 * (0 - (3.8812418236115e-25 + fConst27))) - 3.11856331822835e-23)))));
	fConst44 = (6.88298454448983e-30 * fConst1);
	fConst45 = ((fConst23 * (1.67391212654757e-23 + (fConst1 * (fConst44 - 2.19227421645714e-26)))) - 2.81312195551893e-21);
	fConst46 = (2.14346294728002e-30 * fConst1);
	fConst47 = (fConst23 * ((fConst1 * (5.50549890410771e-27 - fConst46)) - 3.71854410727317e-24));
	fConst48 = (2.12110844225534e-30 * fConst1);
	fConst49 = ((fConst23 * (3.73323141366167e-24 + (fConst1 * (fConst48 - 5.47170430443692e-27)))) - 2.58153923379881e-21);
	fConst50 = (1.72074613612246e-29 * fConst1);
	fConst51 = (1.40656097775947e-21 + (fConst1 * ((fConst1 * (8.36956063273783e-24 + (fConst1 * (2.74034277057142e-26 - fConst50)))) - 9.41252564651073e-22)));
	fConst52 = (5.35865736820004e-30 * fConst1);
	fConst53 = (fConst1 * (1.80284516952507e-22 + (fConst1 * ((fConst1 * (fConst52 - 6.88187363013463e-27)) - 1.85927205363659e-24))));
	fConst54 = (5.30277110563835e-30 * fConst1);
	fConst55 = (1.29076961689941e-21 + (fConst1 * ((fConst1 * (1.86661570683084e-24 + (fConst1 * (6.83963038054615e-27 - fConst54)))) - 2.97931861625272e-22)));
	fConst56 = (5.62624391103787e-21 + (fConst23 * ((2.29432818149661e-29 * fConst23) - 3.34782425309513e-23)));
	fConst57 = (fConst23 * (7.43708821454634e-24 - (7.14487649093339e-30 * fConst23)));
	fConst58 = (5.16307846759763e-21 + (fConst23 * ((7.07036147418447e-30 * fConst23) - 7.46646282732335e-24)));
	fConst59 = (1.40656097775947e-21 + (fConst1 * (9.41252564651073e-22 + (fConst1 * (8.36956063273783e-24 + (fConst1 * (0 - (2.74034277057142e-26 + fConst50))))))));
	fConst60 = (fConst1 * ((fConst1 * ((fConst1 * (6.88187363013463e-27 + fConst52)) - 1.85927205363659e-24)) - 1.80284516952507e-22));
	fConst61 = (1.29076961689941e-21 + (fConst1 * (2.97931861625272e-22 + (fConst1 * (1.86661570683084e-24 + (fConst1 * (0 - (6.83963038054615e-27 + fConst54))))))));
	fConst62 = ((fConst23 * (1.67391212654757e-23 + (fConst1 * (2.19227421645714e-26 + fConst44)))) - 2.81312195551893e-21);
	fConst63 = (fConst23 * ((fConst1 * (0 - (5.50549890410771e-27 + fConst46))) - 3.71854410727317e-24));
	fConst64 = ((fConst23 * (3.73323141366167e-24 + (fConst1 * (5.47170430443692e-27 + fConst48)))) - 2.58153923379881e-21);
	fConst65 = ((fConst1 * ((fConst1 * ((fConst1 * (0 - (5.48068554114285e-27 + fConst13))) - 8.36956063273783e-24)) - 3.13750854883691e-22)) - 1.40656097775947e-21);
	fConst66 = (fConst1 * (6.0094838984169e-23 + (fConst1 * (1.85927205363659e-24 + (fConst1 * (1.37637472602693e-27 + fConst15))))));
	fConst67 = ((fConst1 * ((fConst1 * ((fConst1 * (0 - (1.36792607610923e-27 + fConst17))) - 1.86661570683084e-24)) - 9.93106205417573e-23)) - 1.29076961689941e-21);
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
		double fTemp3 = (1.05586147569038e-17 + (fConst1 * ((fTemp2 * (fConst12 + (fConst10 * fTemp2))) + fConst3)));
		double fTemp4 = (fSlow3 * fTemp0);
		fVec1[0] = fTemp4;
		fRec7[0] = (((0.995 * fRec7[1]) + fVec1[0]) - fVec1[1]);
		fRec6[0] = (fRec7[0] - (((((((fRec6[1] * (6.3351688541423e-17 + (fConst1 * ((fTemp2 * (fConst43 + (fConst42 * fTemp2))) + fConst41)))) + (fRec6[2] * (1.58379221353557e-16 + (fConst1 * ((fTemp2 * (fConst40 + (fConst39 * fTemp2))) + fConst38))))) + (fRec6[3] * (2.11172295138077e-16 + (fConst23 * ((fTemp2 * (fConst37 + (fConst36 * fTemp2))) + fConst35))))) + (fRec6[4] * (1.58379221353557e-16 + (fConst1 * ((fTemp2 * (fConst34 + (fConst32 * fTemp2))) + fConst30))))) + (fRec6[5] * (6.3351688541423e-17 + (fConst1 * ((fTemp2 * (fConst28 + (fConst26 * fTemp2))) + fConst24))))) + (fRec6[6] * (1.05586147569038e-17 + (fConst1 * ((fTemp2 * (fConst21 + (fConst20 * fTemp2))) + fConst19))))) / fTemp3));
		output0[i] = (FAUSTFLOAT)((fSlow4 * fTemp0) + (fConst23 * ((((((((fRec6[0] * ((fTemp2 * (fConst67 + (fConst66 * fTemp2))) + fConst65)) + (fRec6[1] * ((fTemp2 * (fConst64 + (fConst63 * fTemp2))) + fConst62))) + (fRec6[2] * ((fTemp2 * (fConst61 + (fConst60 * fTemp2))) + fConst59))) + (fRec6[3] * ((fTemp2 * (fConst58 + (fConst57 * fTemp2))) + fConst56))) + (fRec6[4] * ((fTemp2 * (fConst55 + (fConst53 * fTemp2))) + fConst51))) + (fRec6[5] * ((fTemp2 * (fConst49 + (fConst47 * fTemp2))) + fConst45))) + (fRec6[6] * ((fTemp2 * (fConst18 + (fConst16 * fTemp2))) + fConst14))) / fTemp3)));
		// post processing
		for (int i=6; i>0; i--) fRec6[i] = fRec6[i-1];
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
