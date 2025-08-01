// generated from file '../src/faust/baxandall.dsp' by dsp2cc:
// Code generated with Faust (https://faust.grame.fr)


namespace baxandall {

class Dsp: public PluginDef {
private:
	int fSampleRate;
	FAUSTFLOAT fVslider0;
	double fRec0[2];
	double fConst0;
	double fConst1;
	double fConst2;
	double fConst3;
	double fConst4;
	double fConst5;
	double fConst6;
	double fConst7;
	double fConst8;
	double fConst9;
	double fConst10;
	double fConst11;
	double fConst12;
	FAUSTFLOAT fVslider1;
	double fRec1[2];
	double fConst13;
	double fConst14;
	double fConst15;
	double fConst16;
	double fConst17;
	double fConst18;
	double fConst19;
	double fConst20;
	double fConst21;
	double fConst22;
	double fConst23;
	double fConst24;
	double fConst25;
	double fConst26;
	double fConst27;
	double fConst28;
	double fConst29;
	double fConst30;
	double fConst31;
	double fConst32;
	double fConst33;
	double fConst34;
	double fConst35;
	double fConst36;
	double fConst37;
	double fConst38;
	double fConst39;
	double fConst40;
	double fConst41;
	double fConst42;
	double fConst43;
	double fConst44;
	double fConst45;
	double fConst46;
	double fConst47;
	double fConst48;
	double fConst49;
	double fConst50;
	double fConst51;
	double fConst52;
	double fConst53;
	double fConst54;
	double fConst55;
	double fConst56;
	double fConst57;
	double fConst58;
	double fConst59;
	double fConst60;
	double fConst61;
	double fConst62;
	double fConst63;
	double fConst64;
	double fConst65;
	double fConst66;
	double fConst67;
	double fConst68;
	double fRec2[5];
	double fConst69;
	double fConst70;
	double fConst71;
	double fConst72;
	double fConst73;
	double fConst74;
	double fConst75;
	double fConst76;
	double fConst77;
	double fConst78;
	double fConst79;
	double fConst80;
	double fConst81;
	double fConst82;
	double fConst83;
	double fConst84;
	double fConst85;
	double fConst86;
	double fConst87;
	double fConst88;
	double fConst89;
	double fConst90;
	double fConst91;
	double fConst92;
	double fConst93;
	double fConst94;
	double fConst95;
	double fConst96;
	double fConst97;
	double fConst98;
	double fConst99;
	double fConst100;
	double fConst101;
	double fConst102;
	double fConst103;

	void clear_state_f();
	int load_ui_f(const UiBuilder& b, int form);
	static const char *glade_def;
	void init(unsigned int sample_rate);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0);
	int register_par(const ParamReg& reg);

	static void clear_state_f_static(PluginDef*);
	static int load_ui_f_static(const UiBuilder& b, int form);
	static void init_static(unsigned int sample_rate, PluginDef*);
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
	category = N_("Tone Control");       // category
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
	for (int l0 = 0; l0 < 2; l0 = l0 + 1) fRec0[l0] = 0.0;
	for (int l1 = 0; l1 < 2; l1 = l1 + 1) fRec1[l1] = 0.0;
	for (int l2 = 0; l2 < 5; l2 = l2 + 1) fRec2[l2] = 0.0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int sample_rate)
{
	fSampleRate = sample_rate;
	fConst0 = std::min<double>(1.92e+05, std::max<double>(1.0, double(fSampleRate)));
	fConst1 = 1.74594889501524e-15 * fConst0;
	fConst2 = mydsp_faustpower2_f(fConst0);
	fConst3 = fConst2 * (-2.060017071488e-12 - fConst1);
	fConst4 = fConst0 * (fConst0 * (fConst1 + 6.82169587607501e-12) + 5.61822837678545e-09);
	fConst5 = 8.20595980657162e-19 * fConst0;
	fConst6 = mydsp_faustpower3_f(fConst0);
	fConst7 = fConst6 * (-7.15839046956248e-15 - fConst5);
	fConst8 = fConst2 * (fConst0 * (fConst5 + 9.39637950771837e-15) + 1.95228830988068e-11);
	fConst9 = fConst6 * (fConst5 + 8.72974447507619e-15);
	fConst10 = fConst2 * (fConst0 * (-1.09677335132321e-14 - fConst5) + -2.38083940229351e-11);
	fConst11 = 3.10334479957618e-19 * fConst0;
	fConst12 = fConst0 * (fConst0 * (fConst0 * (-4.74326697987594e-15 - fConst11) + -1.66212915750803e-11) + -1.36447562277728e-08);
	fConst13 = fConst0 * (fConst0 * (fConst0 * (fConst11 + 4.14900946506348e-15) + 1.38603283669398e-11) + 1.11887001067737e-08);
	fConst14 = 6.60286127569399e-16 * fConst0;
	fConst15 = fConst0 * (fConst0 * (fConst14 + 3.81609719800236e-12) + 5.84773317653659e-09);
	fConst16 = 1.58722626819567e-16 * fConst0;
	fConst17 = fConst2 * (fConst16 + -1.72230935485062e-12);
	fConst18 = 8.19008754388966e-16 * fConst0;
	fConst19 = fConst0 * (fConst0 * (3.24125726288252e-12 - fConst18) + -4.69720733141079e-09);
	fConst20 = 7.45996346051965e-20 * fConst0;
	fConst21 = fConst2 * (fConst0 * (6.50762769960225e-16 - fConst20) + 1.68853858318688e-12);
	fConst22 = 3.84934114562814e-19 * fConst0;
	fConst23 = fConst0 * (fConst0 * (fConst0 * (fConst22 + -3.72011206873759e-15) + 1.47087060946334e-12) + 4.60510522687332e-09);
	fConst24 = fConst6 * (fConst20 + -7.93613134097836e-16);
	fConst25 = fConst2 * (fConst0 * (4.45721994768766e-15 - fConst22) + -3.85293803981734e-12);
	fConst26 = 1.16646701382671e-16 * fConst0;
	fConst27 = fConst0 * (fConst0 * (fConst26 + -1.35752299926304e-12) + 1.24043238434298e-09);
	fConst28 = fConst0 * (fConst0 * (1.13415697533877e-12 - fConst26) + -5.05476196619765e-10);
	fConst29 = 2.48184471026959e-13 * fConst0;
	fConst30 = fConst0 * (fConst29 + -9.9677425108649e-10);
	fConst31 = fConst2 * (fConst1 + -2.060017071488e-12);
	fConst32 = fConst0 * (fConst0 * (6.82169587607501e-12 - fConst1) + -5.61822837678545e-09);
	fConst33 = fConst6 * (7.15839046956248e-15 - fConst5);
	fConst34 = fConst2 * (fConst0 * (fConst5 + -9.39637950771837e-15) + 1.95228830988068e-11);
	fConst35 = fConst6 * (fConst5 + -8.72974447507619e-15);
	fConst36 = fConst2 * (fConst0 * (1.09677335132321e-14 - fConst5) + -2.38083940229351e-11);
	fConst37 = fConst0 * (fConst0 * (fConst0 * (4.74326697987594e-15 - fConst11) + -1.66212915750803e-11) + 1.36447562277728e-08);
	fConst38 = fConst0 * (fConst0 * (fConst0 * (fConst11 + -4.14900946506348e-15) + 1.38603283669398e-11) + -1.11887001067737e-08);
	fConst39 = fConst0 * (fConst0 * (3.81609719800236e-12 - fConst14) + -5.84773317653659e-09);
	fConst40 = 3.49189779003048e-15 * fConst6;
	fConst41 = 3.49189779003048e-15 * fConst2;
	fConst42 = fConst0 * (fConst41 + -1.12364567535709e-08);
	fConst43 = 3.28238392262865e-18 * fConst0;
	fConst44 = fConst43 + -1.4316780939125e-14;
	fConst45 = 1.87927590154367e-14 - fConst43;
	fConst46 = 1.74594889501524e-14 - fConst43;
	fConst47 = fConst43 + -2.19354670264642e-14;
	fConst48 = 1.24133791983047e-18 * fConst0;
	fConst49 = fConst0 * (fConst2 * (fConst48 + -9.48653395975189e-15) + 2.72895124555456e-08);
	fConst50 = fConst0 * (fConst2 * (8.29801893012697e-15 - fConst48) + -2.23774002135474e-08);
	fConst51 = 1.3205722551388e-15 * fConst2;
	fConst52 = fConst0 * (fConst51 + -1.16954663530732e-08);
	fConst53 = mydsp_faustpower4_f(fConst0);
	fConst54 = 4.92357588394297e-18 * fConst53;
	fConst55 = 4.92357588394297e-18 * fConst2;
	fConst56 = fConst2 * (fConst55 + -3.90457661976135e-11);
	fConst57 = fConst2 * (4.76167880458701e-11 - fConst55);
	fConst58 = 1.86200687974571e-18 * fConst2;
	fConst59 = fConst2 * (3.32425831501606e-11 - fConst58);
	fConst60 = fConst2 * (fConst58 + -2.77206567338795e-11);
	fConst61 = fConst0 * (1.12364567535709e-08 - fConst41);
	fConst62 = fConst43 + 1.4316780939125e-14;
	fConst63 = -1.87927590154367e-14 - fConst43;
	fConst64 = -1.74594889501524e-14 - fConst43;
	fConst65 = fConst43 + 2.19354670264642e-14;
	fConst66 = fConst0 * (fConst2 * (fConst48 + 9.48653395975189e-15) + -2.72895124555456e-08);
	fConst67 = fConst0 * (fConst2 * (-8.29801893012697e-15 - fConst48) + 2.23774002135474e-08);
	fConst68 = fConst0 * (1.16954663530732e-08 - fConst51);
	fConst69 = 1.99354850217298e-09 * fConst0;
	fConst70 = 3.17445253639134e-16 * fConst6;
	fConst71 = 1.63801750877793e-15 * fConst2;
	fConst72 = fConst0 * (fConst71 + -9.39441466282157e-09);
	fConst73 = 2.98398538420786e-19 * fConst0;
	fConst74 = fConst6 * (fConst73 + -1.30152553992045e-15);
	fConst75 = 1.53973645825126e-18 * fConst0;
	fConst76 = fConst0 * (fConst2 * (7.44022413747518e-15 - fConst75) + 9.21021045374664e-09);
	fConst77 = 1.58722626819567e-15 - fConst73;
	fConst78 = fConst75 + -8.91443989537532e-15;
	fConst79 = 2.33293402765342e-16 * fConst2;
	fConst80 = fConst0 * (2.48086476868596e-09 - fConst79);
	fConst81 = fConst0 * (fConst79 + -1.01095239323953e-09);
	fConst82 = -3.37707716637377e-12 - 4.47597807631179e-19 * fConst2;
	fConst83 = 2.30960468737688e-18 * fConst2;
	fConst84 = fConst83 + -2.94174121892668e-12;
	fConst85 = 4.47597807631179e-19 * fConst53;
	fConst86 = fConst2 * (7.70587607963469e-12 - fConst83);
	fConst87 = 2.71504599852608e-12 * fConst2;
	fConst88 = fConst0 * (9.39441466282157e-09 - fConst71);
	fConst89 = fConst6 * (fConst73 + 1.30152553992045e-15);
	fConst90 = fConst0 * (fConst2 * (-7.44022413747518e-15 - fConst75) + -9.21021045374664e-09);
	fConst91 = -1.58722626819567e-15 - fConst73;
	fConst92 = fConst75 + 8.91443989537532e-15;
	fConst93 = fConst0 * (fConst79 + -2.48086476868596e-09);
	fConst94 = fConst0 * (1.01095239323953e-09 - fConst79);
	fConst95 = fConst2 * (-1.72230935485062e-12 - fConst16);
	fConst96 = fConst0 * (fConst0 * (fConst18 + 3.24125726288252e-12) + 4.69720733141079e-09);
	fConst97 = fConst2 * (fConst0 * (-6.50762769960225e-16 - fConst20) + 1.68853858318688e-12);
	fConst98 = fConst0 * (fConst0 * (fConst0 * (fConst22 + 3.72011206873759e-15) + 1.47087060946334e-12) + -4.60510522687332e-09);
	fConst99 = fConst6 * (fConst20 + 7.93613134097836e-16);
	fConst100 = fConst2 * (fConst0 * (-4.45721994768766e-15 - fConst22) + -3.85293803981734e-12);
	fConst101 = fConst0 * (fConst0 * (-1.35752299926304e-12 - fConst26) + -1.24043238434298e-09);
	fConst102 = fConst0 * (fConst0 * (fConst26 + 1.13415697533877e-12) + 5.05476196619765e-10);
	fConst103 = fConst0 * (fConst29 + 9.9677425108649e-10);
	clear_state_f();
}

void Dsp::init_static(unsigned int sample_rate, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(sample_rate);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	double fSlow0 = 0.007000000000000006 * double(fVslider0);
	double fSlow1 = 0.007000000000000006 * (1.0 - double(fVslider1));
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		fRec0[0] = fSlow0 + 0.993 * fRec0[1];
		fRec1[0] = fSlow1 + 0.993 * fRec1[1];
		double fTemp0 = fConst15 + fRec1[0] * (fConst13 + fRec1[0] * (fConst12 + fRec0[0] * (fConst10 + fConst9 * fRec0[0])) + fRec0[0] * (fConst8 + fConst7 * fRec0[0])) + fRec0[0] * (fConst4 + fConst3 * fRec0[0]) + 1.89165938612305e-06;
		double fTemp1 = fConst40 * fRec0[0];
		double fTemp2 = fConst54 * fRec0[0];
		fRec2[0] = double(input0[i0]) - (fRec2[1] * (fConst68 + fRec1[0] * (fConst67 + fRec1[0] * (fConst66 + fConst6 * fRec0[0] * (fConst65 + fConst64 * fRec0[0])) + fConst6 * fRec0[0] * (fConst63 + fConst62 * fRec0[0])) + fRec0[0] * (fConst61 + fTemp1) + 7.56663754449219e-06) + fRec2[2] * (fRec1[0] * (fConst60 + fRec1[0] * (fConst59 + fRec0[0] * (fConst57 + fTemp2)) + fRec0[0] * (fConst56 - fTemp2)) + fConst2 * (fRec0[0] * (4.120034142976e-12 * fRec0[0] + -1.364339175215e-11) + -7.63219439600472e-12) + 1.13499563167383e-05) + fRec2[3] * (fConst52 + fRec1[0] * (fConst50 + fRec1[0] * (fConst49 + fConst6 * fRec0[0] * (fConst47 + fConst46 * fRec0[0])) + fConst6 * fRec0[0] * (fConst45 + fConst44 * fRec0[0])) + fRec0[0] * (fConst42 - fTemp1) + 7.56663754449219e-06) + fRec2[4] * (fConst39 + fRec1[0] * (fConst38 + fRec1[0] * (fConst37 + fRec0[0] * (fConst36 + fConst35 * fRec0[0])) + fRec0[0] * (fConst34 + fConst33 * fRec0[0])) + fRec0[0] * (fConst32 + fConst31 * fRec0[0]) + 1.89165938612305e-06)) / fTemp0;
		double fTemp3 = fConst70 * fRec0[0];
		output0[i0] = FAUSTFLOAT((fRec2[0] * (fConst103 + fRec1[0] * (fConst102 + fRec1[0] * (fConst101 + fRec0[0] * (fConst100 + fConst99 * fRec0[0])) + fRec0[0] * (fConst98 + fConst97 * fRec0[0]) + -1.55054048042873e-06) + fRec0[0] * (fConst96 + fConst95 * fRec0[0]) + 1.5815512900373e-06) + fRec2[1] * (fConst69 + fRec1[0] * (fConst94 + fRec1[0] * (fConst93 + fConst6 * fRec0[0] * (fConst92 + fConst91 * fRec0[0])) + fRec0[0] * (fConst90 + fConst89 * fRec0[0]) + -6.20216192171491e-06) + fRec0[0] * (fConst88 + fTemp3) + 6.32620516014921e-06) + fRec2[2] * (fRec1[0] * (fRec1[0] * (fConst87 + fRec0[0] * (fConst86 + fConst85 * fRec0[0])) + fConst2 * (fRec0[0] * (fConst84 + fConst82 * fRec0[0]) + -2.26831395067755e-12) + -9.30324288257237e-06) + fConst2 * (fRec0[0] * (3.44461870970124e-12 * fRec0[0] + -6.48251452576504e-12) + -4.96368942053919e-13) + 9.48930774022381e-06) + fRec2[3] * (fRec1[0] * (fConst81 + fRec1[0] * (fConst80 + fConst6 * fRec0[0] * (fConst78 + fConst77 * fRec0[0])) + fRec0[0] * (fConst76 + fConst74 * fRec0[0]) + -6.20216192171491e-06) + fRec0[0] * (fConst72 - fTemp3) + 6.32620516014921e-06 - fConst69) + fRec2[4] * (fConst30 + fRec1[0] * (fConst28 + fRec1[0] * (fConst27 + fRec0[0] * (fConst25 + fConst24 * fRec0[0])) + fRec0[0] * (fConst23 + fConst21 * fRec0[0]) + -1.55054048042873e-06) + fRec0[0] * (fConst19 + fConst17 * fRec0[0]) + 1.5815512900373e-06)) / fTemp0);
		fRec0[1] = fRec0[0];
		fRec1[1] = fRec1[0];
		for (int j0 = 4; j0 > 0; j0 = j0 - 1) {
			fRec2[j0] = fRec2[j0 - 1];
		}
	}
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerFloatVar("baxandall.ba",N_("bass"),"S","",&fVslider1, 0.5, 0.0, 1.0, 0.01, 0);
	reg.registerFloatVar("baxandall.tr",N_("treble"),"S","",&fVslider0, 0.5, 0.0, 1.0, 0.01, 0);
	return 0;
}

int Dsp::register_params_static(const ParamReg& reg)
{
	return static_cast<Dsp*>(reg.plugin)->register_par(reg);
}

const char *Dsp::glade_def = "\
<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n\
<!-- Generated with glade 3.22.1 -->\n\
<interface>\n\
  <requires lib=\"gtk+\" version=\"3.20\"/>\n\
  <requires lib=\"gxwidgets\" version=\"0.0\"/>\n\
  <object class=\"GtkWindow\" id=\"window1\">\n\
    <property name=\"can_focus\">False</property>\n\
    <child>\n\
      <placeholder/>\n\
    </child>\n\
    <child>\n\
      <object class=\"GtkBox\" id=\"vbox1\">\n\
        <property name=\"visible\">True</property>\n\
        <property name=\"can_focus\">False</property>\n\
        <property name=\"orientation\">vertical</property>\n\
        <child>\n\
          <object class=\"GtkBox\" id=\"rackbox\">\n\
            <property name=\"visible\">True</property>\n\
            <property name=\"can_focus\">False</property>\n\
            <property name=\"spacing\">4</property>\n\
            <child>\n\
              <object class=\"GtkBox\" id=\"hbox1\">\n\
                <property name=\"visible\">True</property>\n\
                <property name=\"can_focus\">False</property>\n\
                <property name=\"spacing\">25</property>\n\
                <child>\n\
                  <object class=\"GtkBox\" id=\"vbox2\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                    <property name=\"orientation\">vertical</property>\n\
                    <child>\n\
                      <object class=\"GtkLabel\" id=\"label1:rack_label\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"label\" translatable=\"yes\">label</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">0</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GxSmallKnobR\" id=\"gxbigknob1\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">True</property>\n\
                        <property name=\"receives_default\">True</property>\n\
                        <property name=\"var_id\">baxandall.ba</property>\n\
                        <property name=\"label_ref\">label1:rack_label</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">1</property>\n\
                      </packing>\n\
                    </child>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"expand\">False</property>\n\
                    <property name=\"fill\">False</property>\n\
                    <property name=\"position\">0</property>\n\
                  </packing>\n\
                </child>\n\
                <child>\n\
                  <object class=\"GtkBox\" id=\"vbox3\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
                    <property name=\"orientation\">vertical</property>\n\
                    <child>\n\
                      <object class=\"GtkLabel\" id=\"label2:rack_label\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">False</property>\n\
                        <property name=\"label\" translatable=\"yes\">label</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">0</property>\n\
                      </packing>\n\
                    </child>\n\
                    <child>\n\
                      <object class=\"GxSmallKnobR\" id=\"gxbigknob2\">\n\
                        <property name=\"visible\">True</property>\n\
                        <property name=\"can_focus\">True</property>\n\
                        <property name=\"receives_default\">True</property>\n\
                        <property name=\"var_id\">baxandall.tr</property>\n\
                        <property name=\"label_ref\">label2:rack_label</property>\n\
                      </object>\n\
                      <packing>\n\
                        <property name=\"expand\">False</property>\n\
                        <property name=\"fill\">False</property>\n\
                        <property name=\"position\">1</property>\n\
                      </packing>\n\
                    </child>\n\
                  </object>\n\
                  <packing>\n\
                    <property name=\"expand\">False</property>\n\
                    <property name=\"fill\">False</property>\n\
                    <property name=\"position\">1</property>\n\
                  </packing>\n\
                </child>\n\
              </object>\n\
              <packing>\n\
                <property name=\"expand\">True</property>\n\
                <property name=\"fill\">False</property>\n\
                <property name=\"pack_type\">end</property>\n\
                <property name=\"position\">0</property>\n\
              </packing>\n\
            </child>\n\
          </object>\n\
          <packing>\n\
            <property name=\"expand\">True</property>\n\
            <property name=\"fill\">False</property>\n\
            <property name=\"position\">0</property>\n\
          </packing>\n\
        </child>\n\
        <child>\n\
          <placeholder/>\n\
        </child>\n\
      </object>\n\
    </child>\n\
  </object>\n\
</interface>\n\
";

inline int Dsp::load_ui_f(const UiBuilder& b, int form)
{
    if (form & UI_FORM_GLADE) {
        b.load_glade(glade_def);
        return 0;
    }
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
