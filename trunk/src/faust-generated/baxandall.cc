// generated from file '../src/faust/baxandall.dsp' by dsp2cc:
// Code generated with Faust 2.15.11 (https://faust.grame.fr)


namespace baxandall {

class Dsp: public PluginDef {
private:
	int fSamplingFreq;
	double fConst0;
	double fConst1;
	double fConst2;
	double fConst3;
	FAUSTFLOAT fVslider0;
	double fRec1[2];
	double fConst4;
	double fConst5;
	double fConst6;
	FAUSTFLOAT fVslider1;
	double fRec2[2];
	double fConst7;
	double fConst8;
	double fConst9;
	double fConst10;
	double fConst11;
	double fConst12;
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
	double fRec0[5];
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
	for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) fRec1[l0] = 0.0;
	for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) fRec2[l1] = 0.0;
	for (int l2 = 0; (l2 < 5); l2 = (l2 + 1)) fRec0[l2] = 0.0;
}

void Dsp::clear_state_f_static(PluginDef *p)
{
	static_cast<Dsp*>(p)->clear_state_f();
}

inline void Dsp::init(unsigned int samplingFreq)
{
	fSamplingFreq = samplingFreq;
	fConst0 = std::min<double>(192000.0, std::max<double>(1.0, double(fSamplingFreq)));
	fConst1 = mydsp_faustpower2_f(fConst0);
	fConst2 = (1.3205722551387999e-15 * fConst1);
	fConst3 = (1.16954663530732e-08 - fConst2);
	fConst4 = (1.24133791983047e-18 * fConst0);
	fConst5 = (((-8.2980189301269704e-15 - fConst4) * fConst1) + 2.23774002135474e-08);
	fConst6 = (((fConst4 + 9.4865339597518906e-15) * fConst1) + -2.72895124555456e-08);
	fConst7 = (3.28238392262865e-18 * fConst0);
	fConst8 = (fConst7 + 2.1935467026464199e-14);
	fConst9 = (-1.7459488950152399e-14 - fConst7);
	fConst10 = (-1.8792759015436701e-14 - fConst7);
	fConst11 = (fConst7 + 1.4316780939125e-14);
	fConst12 = (3.4918977900304798e-15 * fConst1);
	fConst13 = (1.12364567535709e-08 - fConst12);
	fConst14 = (1.8620068797457099e-18 * fConst1);
	fConst15 = (fConst14 + -2.7720656733879499e-11);
	fConst16 = (3.3242583150160602e-11 - fConst14);
	fConst17 = (4.92357588394297e-18 * fConst1);
	fConst18 = (4.7616788045870099e-11 - fConst17);
	fConst19 = ((fConst17 + -3.9045766197613502e-11) * fConst1);
	fConst20 = (0.0 - (4.92357588394297e-18 * mydsp_faustpower4_f(fConst0)));
	fConst21 = (fConst2 + -1.16954663530732e-08);
	fConst22 = (((8.2980189301269704e-15 - fConst4) * fConst1) + -2.23774002135474e-08);
	fConst23 = (((fConst4 + -9.4865339597518906e-15) * fConst1) + 2.72895124555456e-08);
	fConst24 = (fConst7 + -2.1935467026464199e-14);
	fConst25 = (1.7459488950152399e-14 - fConst7);
	fConst26 = (1.8792759015436701e-14 - fConst7);
	fConst27 = (fConst7 + -1.4316780939125e-14);
	fConst28 = ((fConst12 + -1.12364567535709e-08) * fConst0);
	fConst29 = mydsp_faustpower3_f(fConst0);
	fConst30 = (0.0 - (3.4918977900304798e-15 * fConst29));
	fConst31 = (6.6028612756939899e-16 * fConst0);
	fConst32 = (((3.8160971980023599e-12 - fConst31) * fConst0) + -5.8477331765365899e-09);
	fConst33 = (3.1033447995761798e-19 * fConst0);
	fConst34 = (((((fConst33 + -4.1490094650634797e-15) * fConst0) + 1.3860328366939799e-11) * fConst0) + -1.11887001067737e-08);
	fConst35 = (((((4.7432669798759398e-15 - fConst33) * fConst0) + -1.6621291575080301e-11) * fConst0) + 1.36447562277728e-08);
	fConst36 = (8.2059598065716201e-19 * fConst0);
	fConst37 = (((1.0967733513232099e-14 - fConst36) * fConst0) + -2.3808394022935101e-11);
	fConst38 = ((fConst36 + -8.7297444750761903e-15) * fConst0);
	fConst39 = (((fConst36 + -9.3963795077183697e-15) * fConst0) + 1.95228830988068e-11);
	fConst40 = ((7.1583904695624795e-15 - fConst36) * fConst0);
	fConst41 = (1.7459488950152399e-15 * fConst0);
	fConst42 = (((6.8216958760750096e-12 - fConst41) * fConst0) + -5.6182283767854502e-09);
	fConst43 = ((fConst41 + -2.0600170714879998e-12) * fConst0);
	fConst44 = (((fConst31 + 3.8160971980023599e-12) * fConst0) + 5.8477331765365899e-09);
	fConst45 = (((((fConst33 + 4.1490094650634797e-15) * fConst0) + 1.3860328366939799e-11) * fConst0) + 1.11887001067737e-08);
	fConst46 = (((((-4.7432669798759398e-15 - fConst33) * fConst0) + -1.6621291575080301e-11) * fConst0) + -1.36447562277728e-08);
	fConst47 = (((-1.0967733513232099e-14 - fConst36) * fConst0) + -2.3808394022935101e-11);
	fConst48 = ((fConst36 + 8.7297444750761903e-15) * fConst0);
	fConst49 = (((fConst36 + 9.3963795077183697e-15) * fConst0) + 1.95228830988068e-11);
	fConst50 = ((-7.1583904695624795e-15 - fConst36) * fConst0);
	fConst51 = (((fConst41 + 6.8216958760750096e-12) * fConst0) + 5.6182283767854502e-09);
	fConst52 = ((-2.0600170714879998e-12 - fConst41) * fConst0);
	fConst53 = (1.1664670138267101e-16 * fConst0);
	fConst54 = (((fConst53 + 1.13415697533877e-12) * fConst0) + 5.0547619661976502e-10);
	fConst55 = (((-1.35752299926304e-12 - fConst53) * fConst0) + -1.24043238434298e-09);
	fConst56 = (3.8493411456281399e-19 * fConst0);
	fConst57 = (((-4.4572199476876596e-15 - fConst56) * fConst0) + -3.85293803981734e-12);
	fConst58 = (7.4599634605196502e-20 * fConst0);
	fConst59 = ((fConst58 + 7.9361313409783601e-16) * fConst0);
	fConst60 = (((((fConst56 + 3.7201120687375899e-15) * fConst0) + 1.4708706094633399e-12) * fConst0) + -4.6051052268733198e-09);
	fConst61 = ((((-6.5076276996022498e-16 - fConst58) * fConst0) + 1.6885385831868799e-12) * fConst0);
	fConst62 = (2.4818447102695899e-13 * fConst0);
	fConst63 = (fConst62 + 9.9677425108648992e-10);
	fConst64 = (8.1900875438896599e-16 * fConst0);
	fConst65 = (((fConst64 + 3.24125726288252e-12) * fConst0) + 4.6972073314107897e-09);
	fConst66 = (1.58722626819567e-16 * fConst0);
	fConst67 = ((-1.72230935485062e-12 - fConst66) * fConst0);
	fConst68 = (2.3329340276534201e-16 * fConst1);
	fConst69 = (1.01095239323953e-09 - fConst68);
	fConst70 = (fConst68 + -2.4808647686859599e-09);
	fConst71 = (1.53973645825126e-18 * fConst0);
	fConst72 = (fConst71 + 8.9144398953753193e-15);
	fConst73 = (2.9839853842078601e-19 * fConst0);
	fConst74 = (-1.58722626819567e-15 - fConst73);
	fConst75 = (((-7.4402241374751798e-15 - fConst71) * fConst1) + -9.2102104537466396e-09);
	fConst76 = ((fConst73 + 1.30152553992045e-15) * fConst1);
	fConst77 = (1.63801750877793e-15 * fConst1);
	fConst78 = (9.3944146628215694e-09 - fConst77);
	fConst79 = (3.1744525363913401e-16 * fConst1);
	fConst80 = (2.3096046873768799e-18 * fConst1);
	fConst81 = (7.7058760796346898e-12 - fConst80);
	fConst82 = (4.4759780763117903e-19 * fConst1);
	fConst83 = (fConst80 + -2.9417412189266798e-12);
	fConst84 = (-3.37707716637377e-12 - fConst82);
	fConst85 = (fConst68 + -1.01095239323953e-09);
	fConst86 = (2.4808647686859599e-09 - fConst68);
	fConst87 = (fConst71 + -8.9144398953753193e-15);
	fConst88 = (1.58722626819567e-15 - fConst73);
	fConst89 = (((7.4402241374751798e-15 - fConst71) * fConst1) + 9.2102104537466396e-09);
	fConst90 = ((fConst73 + -1.30152553992045e-15) * fConst1);
	fConst91 = ((fConst77 + -9.3944146628215694e-09) * fConst0);
	fConst92 = (0.0 - (3.1744525363913401e-16 * fConst29));
	fConst93 = (1.9935485021729798e-09 * fConst0);
	fConst94 = (((1.13415697533877e-12 - fConst53) * fConst0) + -5.0547619661976502e-10);
	fConst95 = (((fConst53 + -1.35752299926304e-12) * fConst0) + 1.24043238434298e-09);
	fConst96 = (((4.4572199476876596e-15 - fConst56) * fConst0) + -3.85293803981734e-12);
	fConst97 = ((fConst58 + -7.9361313409783601e-16) * fConst0);
	fConst98 = (((((fConst56 + -3.7201120687375899e-15) * fConst0) + 1.4708706094633399e-12) * fConst0) + 4.6051052268733198e-09);
	fConst99 = ((((6.5076276996022498e-16 - fConst58) * fConst0) + 1.6885385831868799e-12) * fConst0);
	fConst100 = (fConst62 + -9.9677425108648992e-10);
	fConst101 = (((3.24125726288252e-12 - fConst64) * fConst0) + -4.6972073314107897e-09);
	fConst102 = ((fConst66 + -1.72230935485062e-12) * fConst0);
	fVslider0 = FAUSTFLOAT(0.5);
	fVslider1 = FAUSTFLOAT(0.5);
	clear_state_f();
}

void Dsp::init_static(unsigned int samplingFreq, PluginDef *p)
{
	static_cast<Dsp*>(p)->init(samplingFreq);
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0)
{
	double fSlow0 = (0.0070000000000000062 * (1.0 - double(fVslider0)));
	double fSlow1 = (0.0070000000000000062 * double(fVslider1));
	for (int i = 0; (i < count); i = (i + 1)) {
		fRec1[0] = (fSlow0 + (0.99299999999999999 * fRec1[1]));
		fRec2[0] = (fSlow1 + (0.99299999999999999 * fRec2[1]));
		double fTemp0 = ((fConst0 * ((fConst44 + (fRec1[0] * ((fConst45 + (fRec1[0] * (fConst46 + (fConst0 * (fRec2[0] * (fConst47 + (fConst48 * fRec2[0]))))))) + (fConst0 * (fRec2[0] * (fConst49 + (fConst50 * fRec2[0]))))))) + (fRec2[0] * (fConst51 + (fConst52 * fRec2[0]))))) + 1.89165938612305e-06);
		fRec0[0] = (double(input0[i]) - (((((fRec0[1] * ((fConst0 * ((fConst3 + (fRec1[0] * ((fConst5 + (fRec1[0] * (fConst6 + (fConst1 * (fRec2[0] * (fConst8 + (fConst9 * fRec2[0]))))))) + (fConst1 * (fRec2[0] * (fConst10 + (fConst11 * fRec2[0]))))))) + (fRec2[0] * (fConst13 + (fConst12 * fRec2[0]))))) + 7.56663754449219e-06)) + (fRec0[2] * (((fRec1[0] * ((fConst1 * (fConst15 + (fRec1[0] * (fConst16 + (fRec2[0] * (fConst18 + (fConst17 * fRec2[0]))))))) + (fRec2[0] * (fConst19 + (fConst20 * fRec2[0]))))) + (fConst1 * ((fRec2[0] * ((4.1200341429759996e-12 * fRec2[0]) + -1.364339175215e-11)) + -7.6321943960047198e-12))) + 1.13499563167383e-05))) + (fRec0[3] * (((fConst0 * (fConst21 + (fRec1[0] * ((fConst22 + (fRec1[0] * (fConst23 + (fConst1 * (fRec2[0] * (fConst24 + (fConst25 * fRec2[0]))))))) + (fConst1 * (fRec2[0] * (fConst26 + (fConst27 * fRec2[0])))))))) + (fRec2[0] * (fConst28 + (fConst30 * fRec2[0])))) + 7.56663754449219e-06))) + (fRec0[4] * ((fConst0 * ((fConst32 + (fRec1[0] * ((fConst34 + (fRec1[0] * (fConst35 + (fConst0 * (fRec2[0] * (fConst37 + (fConst38 * fRec2[0]))))))) + (fConst0 * (fRec2[0] * (fConst39 + (fConst40 * fRec2[0]))))))) + (fRec2[0] * (fConst42 + (fConst43 * fRec2[0]))))) + 1.89165938612305e-06))) / fTemp0));
		output0[i] = FAUSTFLOAT(((((((fRec0[0] * (((fRec1[0] * ((fConst0 * ((fConst54 + (fRec1[0] * (fConst55 + (fConst0 * (fRec2[0] * (fConst57 + (fConst59 * fRec2[0]))))))) + (fRec2[0] * (fConst60 + (fConst61 * fRec2[0]))))) + -1.5505404804287301e-06)) + (fConst0 * (fConst63 + (fRec2[0] * (fConst65 + (fConst67 * fRec2[0])))))) + 1.5815512900373001e-06)) + (fRec0[1] * (((fRec1[0] * ((fConst0 * ((fConst69 + (fRec1[0] * (fConst70 + (fConst1 * (fRec2[0] * (fConst72 + (fConst74 * fRec2[0]))))))) + (fRec2[0] * (fConst75 + (fConst76 * fRec2[0]))))) + -6.2021619217149101e-06)) + (fConst0 * ((fRec2[0] * (fConst78 + (fConst79 * fRec2[0]))) + 1.9935485021729798e-09))) + 6.3262051601492097e-06))) + (fRec0[2] * (((fRec1[0] * ((fConst1 * (((fRec1[0] * ((fRec2[0] * (fConst81 + (fConst82 * fRec2[0]))) + 2.71504599852608e-12)) + -2.2683139506775501e-12) + (fRec2[0] * (fConst83 + (fConst84 * fRec2[0]))))) + -9.3032428825723703e-06)) + (fConst1 * ((fRec2[0] * ((3.44461870970124e-12 * fRec2[0]) + -6.4825145257650401e-12)) + -4.9636894205391899e-13))) + 9.4893077402238103e-06))) + (fRec0[3] * ((((fRec1[0] * ((fConst0 * ((fConst85 + (fRec1[0] * (fConst86 + (fConst1 * (fRec2[0] * (fConst87 + (fConst88 * fRec2[0]))))))) + (fRec2[0] * (fConst89 + (fConst90 * fRec2[0]))))) + -6.2021619217149101e-06)) + (fRec2[0] * (fConst91 + (fConst92 * fRec2[0])))) + 6.3262051601492097e-06) - fConst93))) + (fRec0[4] * (((fRec1[0] * ((fConst0 * ((fConst94 + (fRec1[0] * (fConst95 + (fConst0 * (fRec2[0] * (fConst96 + (fConst97 * fRec2[0]))))))) + (fRec2[0] * (fConst98 + (fConst99 * fRec2[0]))))) + -1.5505404804287301e-06)) + (fConst0 * (fConst100 + (fRec2[0] * (fConst101 + (fConst102 * fRec2[0])))))) + 1.5815512900373001e-06))) / fTemp0));
		fRec1[1] = fRec1[0];
		fRec2[1] = fRec2[0];
		for (int j0 = 4; (j0 > 0); j0 = (j0 - 1)) {
			fRec0[j0] = fRec0[(j0 - 1)];
		}
	}
}

void __rt_func Dsp::compute_static(int count, FAUSTFLOAT *input0, FAUSTFLOAT *output0, PluginDef *p)
{
	static_cast<Dsp*>(p)->compute(count, input0, output0);
}

int Dsp::register_par(const ParamReg& reg)
{
	reg.registerVar("baxandall.ba",N_("bass"),"S","",&fVslider0, 0.5, 0.0, 1.0, 0.01);
	reg.registerVar("baxandall.tr",N_("treble"),"S","",&fVslider1, 0.5, 0.0, 1.0, 0.01);
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
