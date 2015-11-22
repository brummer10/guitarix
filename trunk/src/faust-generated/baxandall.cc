// generated from file '../src/faust/baxandall.dsp' by dsp2cc:
// Code generated with Faust 0.9.65 (http://faust.grame.fr)


namespace baxandall {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	FAUSTFLOAT 	fslider0;
	double 	fRec0[2];
	double 	fConst0;
	double 	fConst1;
	double 	fConst2;
	double 	fConst3;
	double 	fConst4;
	double 	fConst5;
	double 	fConst6;
	double 	fConst7;
	double 	fConst8;
	double 	fConst9;
	double 	fConst10;
	double 	fConst11;
	double 	fConst12;
	double 	fConst13;
	FAUSTFLOAT 	fslider1;
	double 	fRec1[2];
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
	double 	fRec2[5];
	double 	fConst68;
	double 	fConst69;
	double 	fConst70;
	double 	fConst71;
	double 	fConst72;
	double 	fConst73;
	double 	fConst74;
	double 	fConst75;
	double 	fConst76;
	double 	fConst77;
	double 	fConst78;
	double 	fConst79;
	double 	fConst80;
	double 	fConst81;
	double 	fConst82;
	double 	fConst83;
	double 	fConst84;
	double 	fConst85;
	double 	fConst86;
	double 	fConst87;
	double 	fConst88;
	double 	fConst89;
	double 	fConst90;
	double 	fConst91;
	double 	fConst92;
	double 	fConst93;
	double 	fConst94;
	double 	fConst95;
	double 	fConst96;
	double 	fConst97;
	double 	fConst98;
	double 	fConst99;
	double 	fConst100;
	double 	fConst101;
	double 	fConst102;
	void clear_state_f();
	int load_ui_f(const UiBuilder& b, int form);
	void init(unsigned int samplingFreq);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0);
	int register_par(const ParamReg& reg);

	static void clear_state_f_static(PluginDef*);
	static int load_ui_f_static(const UiBuilder& b, int form);
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
	id = "baxandall";
	name = N_("Baxandall");
	groups = 0;
	description = ""; // description (tooltip)
	category = N_("Tone control");       // category
	shortname = "";     // shortname
	mono_audio = compute_static;
	stereo_audio = 0;
	set_samplerate = init_static;
	activate_plugin = 0;
	register_params = register_params_static;
	load_ui = load_ui_f_static;
	clear_state = clear_state_f_static;
	delete_instance = del_instance;
}

Dsp::~Dsp() {
}

inline void Dsp::clear_state_f()
{
	for (int i=0; i<2; i++) fRec0[i] = 0;
	for (int i=0; i<2; i++) fRec1[i] = 0;
	for (int i=0; i<5; i++) fRec2[i] = 0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = double(min(192000, max(1, fSamplingFreq)));
	fConst1 = (1.74594889501524e-15 * fConst0);
	fConst2 = (fConst0 * (0 - (2.060017071488e-12 + fConst1)));
	fConst3 = (5.61822837678545e-09 + (fConst0 * (6.82169587607501e-12 + fConst1)));
	fConst4 = (6.60286127569399e-16 * fConst0);
	fConst5 = (5.84773317653659e-09 + (fConst0 * (3.81609719800236e-12 + fConst4)));
	fConst6 = (8.20595980657162e-19 * fConst0);
	fConst7 = (fConst0 * (0 - (7.15839046956248e-15 + fConst6)));
	fConst8 = (1.95228830988068e-11 + (fConst0 * (9.39637950771837e-15 + fConst6)));
	fConst9 = (3.10334479957618e-19 * fConst0);
	fConst10 = (1.11887001067737e-08 + (fConst0 * (1.38603283669398e-11 + (fConst0 * (4.14900946506348e-15 + fConst9)))));
	fConst11 = (fConst0 * (8.72974447507619e-15 + fConst6));
	fConst12 = ((fConst0 * (0 - (1.09677335132321e-14 + fConst6))) - 2.38083940229351e-11);
	fConst13 = ((fConst0 * ((fConst0 * (0 - (4.74326697987594e-15 + fConst9))) - 1.66212915750803e-11)) - 1.36447562277728e-08);
	fConst14 = (1.58722626819567e-16 * fConst0);
	fConst15 = (fConst0 * (fConst14 - 1.72230935485062e-12));
	fConst16 = (8.19008754388966e-16 * fConst0);
	fConst17 = ((fConst0 * (3.24125726288252e-12 - fConst16)) - 4.69720733141079e-09);
	fConst18 = (2.48184471026959e-13 * fConst0);
	fConst19 = (fConst18 - 9.9677425108649e-10);
	fConst20 = (7.45996346051965e-20 * fConst0);
	fConst21 = (fConst0 * (1.68853858318688e-12 + (fConst0 * (6.50762769960225e-16 - fConst20))));
	fConst22 = (3.84934114562814e-19 * fConst0);
	fConst23 = (4.60510522687332e-09 + (fConst0 * (1.47087060946334e-12 + (fConst0 * (fConst22 - 3.72011206873759e-15)))));
	fConst24 = (1.16646701382671e-16 * fConst0);
	fConst25 = ((fConst0 * (1.13415697533877e-12 - fConst24)) - 5.05476196619765e-10);
	fConst26 = (fConst0 * (fConst20 - 7.93613134097836e-16));
	fConst27 = ((fConst0 * (4.45721994768766e-15 - fConst22)) - 3.85293803981734e-12);
	fConst28 = (1.24043238434298e-09 + (fConst0 * (fConst24 - 1.35752299926304e-12)));
	fConst29 = (fConst0 * (fConst1 - 2.060017071488e-12));
	fConst30 = ((fConst0 * (6.82169587607501e-12 - fConst1)) - 5.61822837678545e-09);
	fConst31 = ((fConst0 * (3.81609719800236e-12 - fConst4)) - 5.84773317653659e-09);
	fConst32 = (fConst0 * (7.15839046956248e-15 - fConst6));
	fConst33 = (1.95228830988068e-11 + (fConst0 * (fConst6 - 9.39637950771837e-15)));
	fConst34 = ((fConst0 * (1.38603283669398e-11 + (fConst0 * (fConst9 - 4.14900946506348e-15)))) - 1.11887001067737e-08);
	fConst35 = (fConst0 * (fConst6 - 8.72974447507619e-15));
	fConst36 = ((fConst0 * (1.09677335132321e-14 - fConst6)) - 2.38083940229351e-11);
	fConst37 = (1.36447562277728e-08 + (fConst0 * ((fConst0 * (4.74326697987594e-15 - fConst9)) - 1.66212915750803e-11)));
	fConst38 = faustpower<3>(fConst0);
	fConst39 = (0 - (3.49189779003048e-15 * fConst38));
	fConst40 = faustpower<2>(fConst0);
	fConst41 = (3.49189779003048e-15 * fConst40);
	fConst42 = (fConst0 * (fConst41 - 1.12364567535709e-08));
	fConst43 = (3.28238392262865e-18 * fConst0);
	fConst44 = (fConst43 - 1.4316780939125e-14);
	fConst45 = (1.87927590154367e-14 - fConst43);
	fConst46 = (1.24133791983047e-18 * fConst0);
	fConst47 = ((fConst40 * (8.29801893012697e-15 - fConst46)) - 2.23774002135474e-08);
	fConst48 = (1.74594889501524e-14 - fConst43);
	fConst49 = (fConst43 - 2.19354670264642e-14);
	fConst50 = (2.72895124555456e-08 + (fConst40 * (fConst46 - 9.48653395975189e-15)));
	fConst51 = (1.3205722551388e-15 * fConst40);
	fConst52 = (fConst51 - 1.16954663530732e-08);
	fConst53 = (0 - (4.92357588394297e-18 * faustpower<4>(fConst0)));
	fConst54 = (4.92357588394297e-18 * fConst40);
	fConst55 = (fConst40 * (fConst54 - 3.90457661976135e-11));
	fConst56 = (4.76167880458701e-11 - fConst54);
	fConst57 = (1.86200687974571e-18 * fConst40);
	fConst58 = (3.32425831501606e-11 - fConst57);
	fConst59 = (fConst57 - 2.77206567338795e-11);
	fConst60 = (1.12364567535709e-08 - fConst41);
	fConst61 = (1.16954663530732e-08 - fConst51);
	fConst62 = (1.4316780939125e-14 + fConst43);
	fConst63 = (0 - (1.87927590154367e-14 + fConst43));
	fConst64 = (2.23774002135474e-08 + (fConst40 * (0 - (8.29801893012697e-15 + fConst46))));
	fConst65 = (0 - (1.74594889501524e-14 + fConst43));
	fConst66 = (2.19354670264642e-14 + fConst43);
	fConst67 = ((fConst40 * (9.48653395975189e-15 + fConst46)) - 2.72895124555456e-08);
	fConst68 = (6.32620516014921e-06 - (1.99354850217298e-09 * fConst0));
	fConst69 = (0 - (3.17445253639134e-16 * fConst38));
	fConst70 = (1.63801750877793e-15 * fConst40);
	fConst71 = (fConst0 * (fConst70 - 9.39441466282157e-09));
	fConst72 = (2.98398538420786e-19 * fConst0);
	fConst73 = (fConst40 * (fConst72 - 1.30152553992045e-15));
	fConst74 = (1.53973645825126e-18 * fConst0);
	fConst75 = (9.21021045374664e-09 + (fConst40 * (7.44022413747518e-15 - fConst74)));
	fConst76 = (1.58722626819567e-15 - fConst72);
	fConst77 = (fConst74 - 8.91443989537532e-15);
	fConst78 = (2.33293402765342e-16 * fConst40);
	fConst79 = (2.48086476868596e-09 - fConst78);
	fConst80 = (fConst78 - 1.01095239323953e-09);
	fConst81 = (4.47597807631179e-19 * fConst40);
	fConst82 = (0 - (3.37707716637377e-12 + fConst81));
	fConst83 = (2.30960468737688e-18 * fConst40);
	fConst84 = (fConst83 - 2.94174121892668e-12);
	fConst85 = (7.70587607963469e-12 - fConst83);
	fConst86 = (3.17445253639134e-16 * fConst40);
	fConst87 = (9.39441466282157e-09 - fConst70);
	fConst88 = (fConst40 * (1.30152553992045e-15 + fConst72));
	fConst89 = ((fConst40 * (0 - (7.44022413747518e-15 + fConst74))) - 9.21021045374664e-09);
	fConst90 = (1.01095239323953e-09 - fConst78);
	fConst91 = (0 - (1.58722626819567e-15 + fConst72));
	fConst92 = (8.91443989537532e-15 + fConst74);
	fConst93 = (fConst78 - 2.48086476868596e-09);
	fConst94 = (fConst0 * (0 - (1.72230935485062e-12 + fConst14)));
	fConst95 = (4.69720733141079e-09 + (fConst0 * (3.24125726288252e-12 + fConst16)));
	fConst96 = (9.9677425108649e-10 + fConst18);
	fConst97 = (fConst0 * (1.68853858318688e-12 + (fConst0 * (0 - (6.50762769960225e-16 + fConst20)))));
	fConst98 = ((fConst0 * (1.47087060946334e-12 + (fConst0 * (3.72011206873759e-15 + fConst22)))) - 4.60510522687332e-09);
	fConst99 = (5.05476196619765e-10 + (fConst0 * (1.13415697533877e-12 + fConst24)));
	fConst100 = (fConst0 * (7.93613134097836e-16 + fConst20));
	fConst101 = ((fConst0 * (0 - (4.45721994768766e-15 + fConst22))) - 3.85293803981734e-12);
	fConst102 = ((fConst0 * (0 - (1.35752299926304e-12 + fConst24))) - 1.24043238434298e-09);
	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	double 	fSlow0 = (0.007000000000000006 * double(fslider0));
	double 	fSlow1 = (0.007000000000000006 * (1.0 - double(fslider1)));
	for (int i=0; i<count; i++) {
		fRec0[0] = ((0.993 * fRec0[1]) + fSlow0);
		fRec1[0] = ((0.993 * fRec1[1]) + fSlow1);
		double fTemp0 = (1.89165938612305e-06 + (fConst0 * (((fRec1[0] * (((fRec1[0] * (fConst13 + (fConst0 * (fRec0[0] * (fConst12 + (fConst11 * fRec0[0])))))) + fConst10) + (fConst0 * (fRec0[0] * (fConst8 + (fConst7 * fRec0[0])))))) + fConst5) + (fRec0[0] * (fConst3 + (fConst2 * fRec0[0]))))));
		fRec2[0] = ((double)input0[i] - (((((fRec2[1] * (7.56663754449219e-06 + (fConst0 * (((fRec1[0] * (((fRec1[0] * (fConst67 + (fConst40 * (fRec0[0] * (fConst66 + (fConst65 * fRec0[0])))))) + fConst64) + (fConst40 * (fRec0[0] * (fConst63 + (fConst62 * fRec0[0])))))) + fConst61) + (fRec0[0] * (fConst60 + (fConst41 * fRec0[0]))))))) + (fRec2[2] * (1.13499563167383e-05 + ((fRec1[0] * ((fConst40 * (fConst59 + (fRec1[0] * (fConst58 + (fRec0[0] * (fConst56 + (fConst54 * fRec0[0]))))))) + (fRec0[0] * (fConst55 + (fConst53 * fRec0[0]))))) + (fConst40 * ((fRec0[0] * ((4.120034142976e-12 * fRec0[0]) - 1.364339175215e-11)) - 7.63219439600472e-12)))))) + (fRec2[3] * (7.56663754449219e-06 + ((fConst0 * (fConst52 + (fRec1[0] * (((fRec1[0] * (fConst50 + (fConst40 * (fRec0[0] * (fConst49 + (fConst48 * fRec0[0])))))) + fConst47) + (fConst40 * (fRec0[0] * (fConst45 + (fConst44 * fRec0[0])))))))) + (fRec0[0] * (fConst42 + (fConst39 * fRec0[0]))))))) + (fRec2[4] * (1.89165938612305e-06 + (fConst0 * (((fRec1[0] * (((fRec1[0] * (fConst37 + (fConst0 * (fRec0[0] * (fConst36 + (fConst35 * fRec0[0])))))) + fConst34) + (fConst0 * (fRec0[0] * (fConst33 + (fConst32 * fRec0[0])))))) + fConst31) + (fRec0[0] * (fConst30 + (fConst29 * fRec0[0])))))))) / fTemp0));
		output0[i] = (FAUSTFLOAT)((((((fRec2[0] * (1.5815512900373e-06 + ((fRec1[0] * ((fConst0 * (((fRec1[0] * (fConst102 + (fConst0 * (fRec0[0] * (fConst101 + (fConst100 * fRec0[0])))))) + fConst99) + (fRec0[0] * (fConst98 + (fConst97 * fRec0[0]))))) - 1.55054048042873e-06)) + (fConst0 * (fConst96 + (fRec0[0] * (fConst95 + (fConst94 * fRec0[0])))))))) + (fRec2[1] * (6.32620516014921e-06 + ((fRec1[0] * ((fConst0 * (((fRec1[0] * (fConst93 + (fConst40 * (fRec0[0] * (fConst92 + (fConst91 * fRec0[0])))))) + fConst90) + (fRec0[0] * (fConst89 + (fConst88 * fRec0[0]))))) - 6.20216192171491e-06)) + (fConst0 * (1.99354850217298e-09 + (fRec0[0] * (fConst87 + (fConst86 * fRec0[0]))))))))) + (fRec2[2] * (9.48930774022381e-06 + ((fRec1[0] * ((fConst40 * (((fRec1[0] * (2.71504599852608e-12 + (fRec0[0] * (fConst85 + (fConst81 * fRec0[0]))))) - 2.26831395067755e-12) + (fRec0[0] * (fConst84 + (fConst82 * fRec0[0]))))) - 9.30324288257237e-06)) + (fConst40 * ((fRec0[0] * ((3.44461870970124e-12 * fRec0[0]) - 6.48251452576504e-12)) - 4.96368942053919e-13)))))) + (fRec2[3] * (((fRec1[0] * ((fConst0 * ((fConst80 + (fRec1[0] * (fConst79 + (fConst40 * (fRec0[0] * (fConst77 + (fConst76 * fRec0[0]))))))) + (fRec0[0] * (fConst75 + (fConst73 * fRec0[0]))))) - 6.20216192171491e-06)) + (fRec0[0] * (fConst71 + (fConst69 * fRec0[0])))) + fConst68))) + (fRec2[4] * (1.5815512900373e-06 + ((fRec1[0] * ((fConst0 * (((fRec1[0] * (fConst28 + (fConst0 * (fRec0[0] * (fConst27 + (fConst26 * fRec0[0])))))) + fConst25) + (fRec0[0] * (fConst23 + (fConst21 * fRec0[0]))))) - 1.55054048042873e-06)) + (fConst0 * (fConst19 + (fRec0[0] * (fConst17 + (fConst15 * fRec0[0]))))))))) / fTemp0);
		// post processing
		for (int i=4; i>0; i--) fRec2[i] = fRec2[i-1];
		fRec1[1] = fRec1[0];
		fRec0[1] = fRec0[0];
	}

}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerVar("baxandall.ba",N_("bass"),"S","",&fslider1, 0.5, 0.0, 1.0, 0.01);
	reg.registerVar("baxandall.tr",N_("treble"),"S","",&fslider0, 0.5, 0.0, 1.0, 0.01);
	return 0;
}

int Dsp::register_params_static(const ParamReg& reg)
{
	return static_cast<Dsp*>(reg.plugin)->register_par(reg);
}

inline int Dsp::load_ui_f(const UiBuilder& b, int form)
{
    if (form & UI_FORM_STACK) {
#define PARAM(p) ("baxandall" "." p)

b.openHorizontalhideBox("");
    b.create_master_slider(PARAM("ba"), "bass");
b.closeBox();
b.openHorizontalBox("");

    b.create_small_rackknobr(PARAM("ba"), "bass");
    b.create_small_rackknobr(PARAM("tr"), "treble");

b.closeBox();

#undef PARAM
        return 0;
    }
	return -1;
}

int Dsp::load_ui_f_static(const UiBuilder& b, int form)
{
	return static_cast<Dsp*>(b.plugin)->load_ui_f(b, form);
}
PluginDef *plugin() {
	return new Dsp();
}

void Dsp::del_instance(PluginDef *p)
{
	delete static_cast<Dsp*>(p);
}

} // end namespace baxandall
