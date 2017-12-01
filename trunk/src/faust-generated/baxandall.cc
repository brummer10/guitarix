// generated from file '../src/faust/baxandall.dsp' by dsp2cc:
// Code generated with Faust 0.9.90 (http://faust.grame.fr)


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
	FAUSTFLOAT 	fslider1;
	double 	fRec1[2];
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
	double 	fRec2[5];
	double 	fConst64;
	double 	fConst65;
	double 	fConst66;
	double 	fConst67;
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

	void clear_state_f();
	int load_ui_f(const UiBuilder& b, int form);
	static const char *glade_def;
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
	fConst0 = double(min(1.92e+05, max(1.0, (double)fSamplingFreq)));
	fConst1 = (1.74594889501524e-15 * fConst0);
	fConst2 = (0 - (2.060017071488e-12 + fConst1));
	fConst3 = (6.82169587607501e-12 + fConst1);
	fConst4 = (8.20595980657162e-19 * fConst0);
	fConst5 = (0 - (7.15839046956248e-15 + fConst4));
	fConst6 = (9.39637950771837e-15 + fConst4);
	fConst7 = (3.10334479957618e-19 * fConst0);
	fConst8 = (1.38603283669398e-11 + (fConst0 * (4.14900946506348e-15 + fConst7)));
	fConst9 = (8.72974447507619e-15 + fConst4);
	fConst10 = (0 - (1.09677335132321e-14 + fConst4));
	fConst11 = ((fConst0 * (0 - (4.74326697987594e-15 + fConst7))) - 1.66212915750803e-11);
	fConst12 = (6.60286127569399e-16 * fConst0);
	fConst13 = (5.84773317653659e-09 + (fConst0 * (3.81609719800236e-12 + fConst12)));
	fConst14 = (1.58722626819567e-16 * fConst0);
	fConst15 = (fConst14 - 1.72230935485062e-12);
	fConst16 = (8.19008754388966e-16 * fConst0);
	fConst17 = (3.24125726288252e-12 - fConst16);
	fConst18 = (2.48184471026959e-13 * fConst0);
	fConst19 = (fConst18 - 9.9677425108649e-10);
	fConst20 = (7.45996346051965e-20 * fConst0);
	fConst21 = (1.68853858318688e-12 + (fConst0 * (6.50762769960225e-16 - fConst20)));
	fConst22 = (3.84934114562814e-19 * fConst0);
	fConst23 = (1.47087060946334e-12 + (fConst0 * (fConst22 - 3.72011206873759e-15)));
	fConst24 = (fConst20 - 7.93613134097836e-16);
	fConst25 = (4.45721994768766e-15 - fConst22);
	fConst26 = (1.16646701382671e-16 * fConst0);
	fConst27 = (fConst26 - 1.35752299926304e-12);
	fConst28 = ((fConst0 * (1.13415697533877e-12 - fConst26)) - 5.05476196619765e-10);
	fConst29 = (fConst1 - 2.060017071488e-12);
	fConst30 = (6.82169587607501e-12 - fConst1);
	fConst31 = (7.15839046956248e-15 - fConst4);
	fConst32 = (fConst4 - 9.39637950771837e-15);
	fConst33 = (1.38603283669398e-11 + (fConst0 * (fConst7 - 4.14900946506348e-15)));
	fConst34 = (fConst4 - 8.72974447507619e-15);
	fConst35 = (1.09677335132321e-14 - fConst4);
	fConst36 = ((fConst0 * (4.74326697987594e-15 - fConst7)) - 1.66212915750803e-11);
	fConst37 = ((fConst0 * (3.81609719800236e-12 - fConst12)) - 5.84773317653659e-09);
	fConst38 = (3.28238392262865e-18 * fConst0);
	fConst39 = (fConst38 - 1.4316780939125e-14);
	fConst40 = (1.87927590154367e-14 - fConst38);
	fConst41 = (1.24133791983047e-18 * fConst0);
	fConst42 = (8.29801893012697e-15 - fConst41);
	fConst43 = faustpower<2>(fConst0);
	fConst44 = (1.74594889501524e-14 - fConst38);
	fConst45 = (fConst38 - 2.19354670264642e-14);
	fConst46 = (fConst41 - 9.48653395975189e-15);
	fConst47 = (1.3205722551388e-15 * fConst43);
	fConst48 = (fConst47 - 1.16954663530732e-08);
	fConst49 = faustpower<3>(fConst0);
	fConst50 = (0 - (3.49189779003048e-15 * fConst49));
	fConst51 = (fConst0 * ((3.49189779003048e-15 * fConst43) - 1.12364567535709e-08));
	fConst52 = (1.86200687974571e-18 * fConst43);
	fConst53 = (3.32425831501606e-11 - fConst52);
	fConst54 = (fConst52 - 2.77206567338795e-11);
	fConst55 = (0 - (4.92357588394297e-18 * faustpower<4>(fConst0)));
	fConst56 = (fConst43 * ((4.92357588394297e-18 * fConst43) - 3.90457661976135e-11));
	fConst57 = (1.87927590154367e-14 + fConst38);
	fConst58 = (1.4316780939125e-14 + fConst38);
	fConst59 = (0 - (8.29801893012697e-15 + fConst41));
	fConst60 = (0 - (1.74594889501524e-14 + fConst38));
	fConst61 = (2.19354670264642e-14 + fConst38);
	fConst62 = (9.48653395975189e-15 + fConst41);
	fConst63 = (1.16954663530732e-08 - fConst47);
	fConst64 = (2.98398538420786e-19 * fConst0);
	fConst65 = (fConst64 - 1.30152553992045e-15);
	fConst66 = (1.53973645825126e-18 * fConst0);
	fConst67 = (7.44022413747518e-15 - fConst66);
	fConst68 = (1.58722626819567e-15 - fConst64);
	fConst69 = (fConst66 - 8.91443989537532e-15);
	fConst70 = (2.33293402765342e-16 * fConst43);
	fConst71 = (fConst70 - 1.01095239323953e-09);
	fConst72 = (0 - (3.17445253639134e-16 * fConst49));
	fConst73 = (fConst0 * ((1.63801750877793e-15 * fConst43) - 9.39441466282157e-09));
	fConst74 = (6.32620516014921e-06 - (1.99354850217298e-09 * fConst0));
	fConst75 = (0 - (3.37707716637377e-12 + (4.47597807631179e-19 * fConst43)));
	fConst76 = ((2.30960468737688e-18 * fConst43) - 2.94174121892668e-12);
	fConst77 = (1.30152553992045e-15 + fConst64);
	fConst78 = (0 - (7.44022413747518e-15 + fConst66));
	fConst79 = (0 - (1.58722626819567e-15 + fConst64));
	fConst80 = (8.91443989537532e-15 + fConst66);
	fConst81 = (1.01095239323953e-09 - fConst70);
	fConst82 = (0 - (1.72230935485062e-12 + fConst14));
	fConst83 = (3.24125726288252e-12 + fConst16);
	fConst84 = (9.9677425108649e-10 + fConst18);
	fConst85 = (1.68853858318688e-12 + (fConst0 * (0 - (6.50762769960225e-16 + fConst20))));
	fConst86 = (1.47087060946334e-12 + (fConst0 * (3.72011206873759e-15 + fConst22)));
	fConst87 = (7.93613134097836e-16 + fConst20);
	fConst88 = (0 - (4.45721994768766e-15 + fConst22));
	fConst89 = (0 - (1.35752299926304e-12 + fConst26));
	fConst90 = (5.05476196619765e-10 + (fConst0 * (1.13415697533877e-12 + fConst26)));
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
		fRec0[0] = (fSlow0 + (0.993 * fRec0[1]));
		fRec1[0] = (fSlow1 + (0.993 * fRec1[1]));
		double fTemp0 = (1.89165938612305e-06 + (fConst0 * (fConst13 + ((fRec1[0] * (1.11887001067737e-08 + ((fRec1[0] * ((fConst0 * (fConst11 + (fRec0[0] * ((fConst0 * (fConst10 + (fConst9 * fRec0[0]))) - 2.38083940229351e-11)))) - 1.36447562277728e-08)) + (fConst0 * (fConst8 + (fRec0[0] * (1.95228830988068e-11 + (fConst0 * (fConst6 + (fConst5 * fRec0[0])))))))))) + (fRec0[0] * (5.61822837678545e-09 + (fConst0 * (fConst3 + (fConst2 * fRec0[0])))))))));
		fRec2[0] = ((double)input0[i] - (((((fRec2[1] * (7.56663754449219e-06 + (fConst0 * (fConst63 + ((fRec1[0] * (2.23774002135474e-08 + ((fRec1[0] * ((fConst43 * (fConst62 + (fRec0[0] * (fConst61 + (fConst60 * fRec0[0]))))) - 2.72895124555456e-08)) + (fConst43 * (fConst59 + (fRec0[0] * ((fConst58 * fRec0[0]) - fConst57))))))) + (fRec0[0] * (1.12364567535709e-08 + (fConst43 * ((3.49189779003048e-15 * fRec0[0]) - 3.49189779003048e-15))))))))) + (fRec2[2] * (1.13499563167383e-05 + ((fConst43 * ((fRec0[0] * ((4.120034142976e-12 * fRec0[0]) - 1.364339175215e-11)) - 7.63219439600472e-12)) + (fRec1[0] * ((fRec0[0] * (fConst56 + (fConst55 * fRec0[0]))) + (fConst43 * (fConst54 + (fRec1[0] * (fConst53 + (fRec0[0] * (4.76167880458701e-11 + (fConst43 * ((4.92357588394297e-18 * fRec0[0]) - 4.92357588394297e-18)))))))))))))) + (fRec2[3] * (7.56663754449219e-06 + ((fRec0[0] * (fConst51 + (fConst50 * fRec0[0]))) + (fConst0 * (fConst48 + (fRec1[0] * (((fRec1[0] * (2.72895124555456e-08 + (fConst43 * (fConst46 + (fRec0[0] * (fConst45 + (fConst44 * fRec0[0]))))))) + (fConst43 * (fConst42 + (fRec0[0] * (fConst40 + (fConst39 * fRec0[0])))))) - 2.23774002135474e-08)))))))) + (fRec2[4] * (1.89165938612305e-06 + (fConst0 * (fConst37 + ((fRec1[0] * (((fRec1[0] * (1.36447562277728e-08 + (fConst0 * (fConst36 + (fRec0[0] * ((fConst0 * (fConst35 + (fConst34 * fRec0[0]))) - 2.38083940229351e-11)))))) + (fConst0 * (fConst33 + (fRec0[0] * (1.95228830988068e-11 + (fConst0 * (fConst32 + (fConst31 * fRec0[0])))))))) - 1.11887001067737e-08)) + (fRec0[0] * ((fConst0 * (fConst30 + (fConst29 * fRec0[0]))) - 5.61822837678545e-09)))))))) / fTemp0));
		output0[i] = (FAUSTFLOAT)((((((fRec2[0] * (1.5815512900373e-06 + ((fRec1[0] * ((fConst0 * (fConst90 + ((fRec1[0] * ((fConst0 * (fConst89 + (fRec0[0] * ((fConst0 * (fConst88 + (fConst87 * fRec0[0]))) - 3.85293803981734e-12)))) - 1.24043238434298e-09)) + (fRec0[0] * ((fConst0 * (fConst86 + (fConst85 * fRec0[0]))) - 4.60510522687332e-09))))) - 1.55054048042873e-06)) + (fConst0 * (fConst84 + (fRec0[0] * (4.69720733141079e-09 + (fConst0 * (fConst83 + (fConst82 * fRec0[0])))))))))) + (fRec2[1] * (6.32620516014921e-06 + ((fRec1[0] * ((fConst0 * (fConst81 + ((fRec1[0] * ((fConst43 * (2.33293402765342e-16 + (fRec0[0] * (fConst80 + (fConst79 * fRec0[0]))))) - 2.48086476868596e-09)) + (fRec0[0] * ((fConst43 * (fConst78 + (fConst77 * fRec0[0]))) - 9.21021045374664e-09))))) - 6.20216192171491e-06)) + (fConst0 * (1.99354850217298e-09 + (fRec0[0] * (9.39441466282157e-09 + (fConst43 * ((3.17445253639134e-16 * fRec0[0]) - 1.63801750877793e-15)))))))))) + (fRec2[2] * (9.48930774022381e-06 + ((fConst43 * ((fRec0[0] * ((3.44461870970124e-12 * fRec0[0]) - 6.48251452576504e-12)) - 4.96368942053919e-13)) + (fRec1[0] * ((fConst43 * (((fRec0[0] * (fConst76 + (fConst75 * fRec0[0]))) + (fRec1[0] * (2.71504599852608e-12 + (fRec0[0] * (7.70587607963469e-12 + (fConst43 * ((4.47597807631179e-19 * fRec0[0]) - 2.30960468737688e-18))))))) - 2.26831395067755e-12)) - 9.30324288257237e-06)))))) + (fRec2[3] * (fConst74 + ((fRec0[0] * (fConst73 + (fConst72 * fRec0[0]))) + (fRec1[0] * ((fConst0 * (fConst71 + ((fRec1[0] * (2.48086476868596e-09 + (fConst43 * ((fRec0[0] * (fConst69 + (fConst68 * fRec0[0]))) - 2.33293402765342e-16)))) + (fRec0[0] * (9.21021045374664e-09 + (fConst43 * (fConst67 + (fConst65 * fRec0[0])))))))) - 6.20216192171491e-06)))))) + (fRec2[4] * (1.5815512900373e-06 + ((fRec1[0] * ((fConst0 * (fConst28 + ((fRec1[0] * (1.24043238434298e-09 + (fConst0 * (fConst27 + (fRec0[0] * ((fConst0 * (fConst25 + (fConst24 * fRec0[0]))) - 3.85293803981734e-12)))))) + (fRec0[0] * (4.60510522687332e-09 + (fConst0 * (fConst23 + (fConst21 * fRec0[0])))))))) - 1.55054048042873e-06)) + (fConst0 * (fConst19 + (fRec0[0] * ((fConst0 * (fConst17 + (fConst15 * fRec0[0]))) - 4.69720733141079e-09)))))))) / fTemp0);
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

const char *Dsp::glade_def = "\
<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n\
<interface>\n\
  <!-- interface-requires gxwidgets 0.0 -->\n\
  <requires lib=\"gtk+\" version=\"2.20\"/>\n\
  <!-- interface-naming-policy project-wide -->\n\
  <object class=\"GtkWindow\" id=\"window1\">\n\
    <property name=\"can_focus\">False</property>\n\
    <child>\n\
      <object class=\"GtkVBox\" id=\"vbox1\">\n\
        <property name=\"visible\">True</property>\n\
        <property name=\"can_focus\">False</property>\n\
        <child>\n\
          <object class=\"GtkHBox\" id=\"rackbox\">\n\
            <property name=\"visible\">True</property>\n\
            <property name=\"can_focus\">False</property>\n\
            <property name=\"spacing\">4</property>\n\
            <child>\n\
              <object class=\"GtkHBox\" id=\"hbox1\">\n\
                <property name=\"visible\">True</property>\n\
                <property name=\"can_focus\">False</property>\n\
                <property name=\"spacing\">25</property>\n\
                <child>\n\
                  <object class=\"GtkVBox\" id=\"vbox2\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
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
                  <object class=\"GtkVBox\" id=\"vbox3\">\n\
                    <property name=\"visible\">True</property>\n\
                    <property name=\"can_focus\">False</property>\n\
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
